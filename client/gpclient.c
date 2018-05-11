/*
 * gpclient.c -- client program for the guiderport
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include <stdlib.h>
#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

static int	debug = 0;

/*
 * we have to find out whether this is a sufficiently modern libusb.
 * unfortunately, older libusb implementations have no way to tell 
 * what version they are. But maybe the presence of the LIBUSB_ERROR_COUNT
 * preprocessor symbol allows us to recognize sufficiently modern 
 * libusb for a full implementation
 */

#ifndef LIBUSB_ERROR_COUNT
#define LIBUSB_LOG_LEVEL_INFO	3
#define LIBUSB_LOG_LEVEL_DEBUG	4
char	*libusb_strerror(int rc) {
	switch (rc) {
	case  0:
		return "Success";
	case -1:
		return "IO error";
	case -2:
		return "invalid parameter";
	case -3:
		return "access denied";
	case -4:
		return "no device";
	case -5:
		return "not found";
	case -6:
		return "busy";
	case -7:
		return "timeout";
	case -8:
		return "overflow";
	case -9:
		return "pipe error";
	case -10:
		return "system call interrupted";
	case -11:
		return "insufficient memory";
	case -12:
		return "not supported";
	}
	return "other error";
}
#endif /* LIBUSB_ERROR_COUNT */

/*
 * commands understood by the GuiderPort device
 */
#define GUIDERPORT_RESET		0
#define GUIDERPORT_SET			1
#define GUIDERPORT_SET_PORT_TIME	2
#define GUIDERPORT_SET_ALL_TIMES	3
#define GUIDERPORT_GET			4
#define GUIDERPORT_SERIAL		5

static int	max_retries = 3;

char    *read_string(libusb_device_handle *handle, int stringid) {
	int     rc;
	unsigned char   *s = (unsigned char *)malloc(128);
	int     retries = 0;
	do {
		rc = libusb_get_string_descriptor_ascii(handle,
				stringid, s, 128);
		if (rc >= 0) {
			return (char *)s;
		}
		if (debug) {
			fprintf(stderr, "error: %s (%d)",
				libusb_error_name(rc), rc);
		} else {
			fprintf(stderr, ".");
			fflush(stderr);
		}
	} while (max_retries > ++retries);
	snprintf((char *)s, 128, "last error: %s (%d)",
		libusb_error_name(rc), rc);
	return (char *)s;
}





/*
 * display the descriptors, for tesing
 */
int	show_descriptors(libusb_device_handle *handle) {
	libusb_device	*device = libusb_get_device(handle);

	// get the descriptors
	struct libusb_device_descriptor	device_descriptor;
	libusb_get_device_descriptor(device, &device_descriptor);
	printf("bLength:            %d\n", device_descriptor.bLength);
	printf("bDescriptorType:    %d\n", device_descriptor.bDescriptorType);
	printf("bcdUSB:             %x\n", device_descriptor.bcdUSB);
	printf("bDeviceClass:       %x\n", device_descriptor.bDeviceClass);
	printf("bDeviceSubClass:    %x\n", device_descriptor.bDeviceSubClass);
	printf("bDeviceProtocol:    %x\n", device_descriptor.bDeviceProtocol);
	printf("bMaxPacketSize0:    %d\n", device_descriptor.bMaxPacketSize0);
	printf("idVendor:           0x%04x\n", device_descriptor.idVendor);
	printf("idProduct:          0x%04x\n", device_descriptor.idProduct);
	if (device_descriptor.iManufacturer) {
		char	*s = read_string(handle,
				device_descriptor.iManufacturer);
		printf("Manufacturer:       %s\n", s);
		free(s);
	}
	if (device_descriptor.iProduct) {
		char	*s = read_string(handle,
				device_descriptor.iProduct);
		printf("Product:            %s\n", s);
		free(s);
	}
	if (device_descriptor.iSerialNumber) {
		char	*s = read_string(handle,
				device_descriptor.iSerialNumber);
		printf("Serial Number:      %s\n", s);
		free(s);
	}
	printf("bNumConfigurations: %d\n", device_descriptor.bNumConfigurations);

	struct libusb_config_descriptor	*config_descriptor;
	if (libusb_get_config_descriptor(device, 0, &config_descriptor)) {
		fprintf(stderr, "cannot get config descriptor\n");
		return EXIT_FAILURE;
	}
	printf("    bLength:              %d\n",
		config_descriptor->bLength);
	printf("    bDescriptorType:      %d\n",
		config_descriptor->bDescriptorType);
	printf("    wTotalLength:         %d\n",
		config_descriptor->wTotalLength);
	printf("    bNumInterfaces:       %d\n",
		config_descriptor->bNumInterfaces);
	printf("    bConfigurationValue:  %d\n",
		config_descriptor->bConfigurationValue);
	if (config_descriptor->iConfiguration) {
		char	*s = read_string(handle,
				config_descriptor->iConfiguration);
		printf("Serial Number:      %s\n", s);
		free(s);
	}
	printf("    bmAttributes:         %d\n",
		config_descriptor->bmAttributes);
	printf("    MaxPower:             %d\n",
		2 * config_descriptor->MaxPower);
	return EXIT_SUCCESS;
}

void	show_version() {
	const struct libusb_version* version;
	version = libusb_get_version();
	printf("libusb version: %d.%d.%d.%d\n",
		version->major, version->minor, version->micro, version->nano);
}

/*
 * Show usage message
 */
void	usage(const char *progname) {
	printf("usage:\n");
	printf("  %s [ options ] descriptors\n", progname);
	printf("  %s [ options ] set <value>\n", progname);
	printf("  %s [ options ] get\n", progname);
	printf("  %s [ options ] port <port> <time>\n", progname);
	printf("  %s [ options ] times <value0> <value1> <value2> <value3>\n",
		progname);
	printf("  %s [ options ] serial <serial>\n", progname);
	printf("  %s [ options ] reset\n", progname);
	printf("  %s [ options ] help\n", progname);
	printf("options:\n");
	printf(" -d,--debug             enablue USB debugging\n");
	printf(" -h,-?,--help           display this help and exit\n");
	printf(" -V,--version           show version of USB library and exit\n");
	printf(" -v,--vendor=<vid>      use this vendor id to connect\n");
	printf(" -p,--product=<pid>     use this product id to connect\n");
	printf(" -r,--repeat=<repeat>   how often to repeat the times command\n");
	printf(" -s,--sleep=<sleep>     how long to sleep in ms after each times command\n");
}

static struct option	longopts[] = {
{ "debug",	no_argument,		NULL,	'd' },
{ "help",	no_argument,		NULL,	'h' },
{ "product",	required_argument,	NULL,	'p' },
{ "repeat",	required_argument,	NULL,	'r' },
{ "sleep",	required_argument,	NULL,	's' },
{ "vendor",	required_argument,	NULL,	'v' },
{ "version",	no_argument,		NULL,	'V' },
{ NULL,		0,			NULL,	0   }
};

/*
 * Main function of the client program
 */
int	main(int argc, char *argv[]) {
	// parse command line
	int	c;
	uint16_t	vid = 0xf055;
	uint16_t	pid = 0x1234;
	int	repeat = 1;
	int	sleeptime = 0;
	int	longindex;
	while (EOF != (c = getopt_long(argc, argv, "dh?v:p:Vr:s:",
		longopts, &longindex)))
		switch (c) {	
		case 'd':
			debug = 1;
			break;
		case 'h':
		case '?':
			usage(argv[0]);
			return EXIT_SUCCESS;
		case 'v':
			vid = atoi(optarg);
			break;
		case 'p':
			pid = atoi(optarg);
			break;
		case 'r':
			repeat = atoi(optarg);
			if (0 == repeat) {
				repeat = -1;
			}
			break;
		case 's':
			sleeptime = atoi(optarg);
			break;
		case 'V':
			show_version();
			return EXIT_SUCCESS;
		}

	// get the command
	if (optind >= argc) {
		fprintf(stderr, "command argument missing\n");
		return EXIT_FAILURE;
	}
	char	*command = argv[optind++];

	// help command
	if (0 == strcmp(command, "help")) {
		usage(argv[0]);
		return EXIT_SUCCESS;
	}

	// initialize libusb library
	libusb_context	*context;
	libusb_init(&context);
	libusb_set_debug(context,
		(debug) ? LIBUSB_LOG_LEVEL_DEBUG : LIBUSB_LOG_LEVEL_INFO);

	// connect to the device
	libusb_device_handle *handle;
	handle = libusb_open_device_with_vid_pid(context, vid, pid);
	if (NULL == handle) {
		fprintf(stderr, "cannot open device\n");
		return EXIT_FAILURE;
	}

	// process the descriptors command
	if (0 == strcmp(command, "descriptors")) {
		return show_descriptors(handle);
	}

	// commands below may need to evaluate the USB return code
	int		rc;

	// all commands need value and index, so we allocate these variables
	// only once
	uint16_t	value;
	uint16_t	index;

	// set command implementation
	if (0 == strcmp(command, "set")) {
		if (optind >= argc) {
			fprintf(stderr, "no argument to set given\n");
			return EXIT_SUCCESS;
		}
		value = atoi(argv[optind++]);
		index = 0xf;
		rc = libusb_control_transfer(handle,
			LIBUSB_REQUEST_TYPE_VENDOR |
			LIBUSB_RECIPIENT_DEVICE |
			LIBUSB_ENDPOINT_OUT, GUIDERPORT_SET, 
			value, index, NULL, 0, 1000);
		if (rc) {
			fprintf(stderr, "cannot send SET: %s\n", 
				libusb_strerror(rc));
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	// set command implementation
	if (0 == strcmp(command, "get")) {
		index = 0xf;
		unsigned char	result;
		rc = libusb_control_transfer(handle,
			LIBUSB_REQUEST_TYPE_VENDOR |
			LIBUSB_RECIPIENT_DEVICE |
			LIBUSB_ENDPOINT_IN, GUIDERPORT_GET, 
			0, index, &result, 1, 1000);
		if (rc < 0) {
			fprintf(stderr, "cannot send GET: %s\n", 
				libusb_strerror(rc));
			return EXIT_FAILURE;
		}
		if (rc != 1) {
			fprintf(stderr, "state not received");
			return EXIT_FAILURE;
		}
		printf("status: %d\n", result);
		return EXIT_SUCCESS;
	}


	// port command implementation
	if (0 == strcmp(command, "port")) {
		if (optind >= argc - 1) {
			fprintf(stderr, "port command needs two paramters\n");
			return EXIT_FAILURE;
		}
		index = atoi(argv[optind++]);
		value = atoi(argv[optind++]);
		if (index > 3) {
			fprintf(stderr, "invalid port: %d\n", index);
			return EXIT_FAILURE;
		}
		printf("port: %d, time: %d\n", index, value);
		rc = libusb_control_transfer(handle,
			LIBUSB_REQUEST_TYPE_VENDOR |
			LIBUSB_RECIPIENT_DEVICE |
			LIBUSB_ENDPOINT_OUT, GUIDERPORT_SET_PORT_TIME, 
			value, index, NULL, 0, 1000);
		if (rc) {
			fprintf(stderr, "cannot send SET_PORT_TIME: %s\n", 
				libusb_strerror(rc));
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	// times command implementation
	if (0 == strcmp(command, "times")) {
		if (optind >= argc - 3) {
			fprintf(stderr, "times command needs 4 parameters\n");
			return EXIT_FAILURE;
		}
		uint16_t	porttimes[4];
		for (int i = 0; i < 4; i++) {
			porttimes[i] = atoi(argv[optind++]);
		}
		index = 0;
		value = 0;
		while (repeat--) {
			rc = libusb_control_transfer(handle,
				LIBUSB_REQUEST_TYPE_VENDOR |
				LIBUSB_RECIPIENT_DEVICE |
				LIBUSB_ENDPOINT_OUT, GUIDERPORT_SET_ALL_TIMES, 
				value, index, (void *)porttimes, 8, 1000);
			if (rc < 0) {
				fprintf(stderr,
					"cannot send SET_ALL_TIMES: %s (%d)\n", 
					libusb_strerror(rc), rc);
				return EXIT_FAILURE;
			}
			if (8 != rc) {
			fprintf(stderr, "cannot send all bytes\n");
				return EXIT_FAILURE;
			}
			if (sleeptime) {
				usleep(1000 * sleeptime);
			}
		}
		return EXIT_SUCCESS;
	}

	// serial command
	if (0 == strcmp(command, "serial")) {
		char    *newserial = argv[optind];
		int     l = strlen(newserial);
		if (l > 7) {
			fprintf(stderr, "serial string too long\n");
			return EXIT_FAILURE;
		}
		rc = libusb_control_transfer(handle,
			LIBUSB_REQUEST_TYPE_VENDOR |
			LIBUSB_RECIPIENT_DEVICE |
			LIBUSB_ENDPOINT_OUT, GUIDERPORT_SERIAL,
			0, 0, (unsigned char *)newserial, l, 1000);
		if (rc < 0) {
			fprintf(stderr, "cannot send SERIAL '%s': %s\n",
				newserial, libusb_strerror(rc));
			return EXIT_FAILURE;
		}
		if (rc != l) {
			fprintf(stderr, "cannot send %d bytes: %d\n", l, rc);
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	// reset command
	if (0 == strcmp(command, "reset")) {
		index = 0;
		value = 0;
		rc = libusb_control_transfer(handle,
			LIBUSB_REQUEST_TYPE_VENDOR |
			LIBUSB_RECIPIENT_DEVICE |
			LIBUSB_ENDPOINT_OUT, GUIDERPORT_RESET, 
			value, index, NULL, 0, 1000);
		if (rc) {
			fprintf(stderr, "cannot send RESET: %s (%d)\n", 
				libusb_strerror(rc), rc);
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	// command was not interpreted
	fprintf(stderr, "unknown command '%s'\n", command);
	return EXIT_FAILURE;
}
