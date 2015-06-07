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

#define GUIDERPORT_RESET		0
#define GUIDERPORT_SET			1
#define GUIDERPORT_SET_PORT_TIME	2
#define GUIDERPORT_SET_ALL_TIMES	3

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
	unsigned char	s[128];
	if (device_descriptor.iManufacturer) {
		libusb_get_string_descriptor_ascii(handle,
			device_descriptor.iManufacturer, s, sizeof(s));
		printf("Manufacturer:       %s\n", s);
	}
	if (device_descriptor.iProduct) {
		libusb_get_string_descriptor_ascii(handle,
			device_descriptor.iProduct, s, sizeof(s));
		printf("Product:            %s\n", s);
	}
	if (device_descriptor.iSerialNumber) {
		libusb_get_string_descriptor_ascii(handle,
			device_descriptor.iSerialNumber, s, sizeof(s));
		printf("Serial Number:      %s\n", s);
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
		libusb_get_string_descriptor_ascii(handle,
			config_descriptor->iConfiguration, s, sizeof(s));
		printf("Serial Number:      %s\n", s);
	}
	printf("    bmAttributes:         %d\n",
		config_descriptor->bmAttributes);
	printf("    MaxPoser:             %d\n",
		2 * config_descriptor->MaxPower);
	return EXIT_SUCCESS;
}

void	show_version() {
	const struct libusb_version* version;
	version = libusb_get_version();
	printf("libusb version: %d.%d.%d.%d\n",
		version->major, version->minor, version->micro, version->nano);
}

void	usage(const char *progname) {
	printf("usage:\n");
	printf("  %s [ options ] descriptors\n", progname);
	printf("  %s [ options ] set <value>\n", progname);
	printf("  %s [ options ] port <port> <time>\n", progname);
	printf("  %s [ options ] times <value0> <value1> <value2> <value3>\n", progname);
	printf("  %s [ options ] reset\n", progname);
	printf("options:\n");
	printf(" -d         enablue USB debugging\n");
	printf(" -h,-?      display this help and exit\n");
	printf(" -V         show version of USB library and exit\n");
	printf(" -v <vid>   use this vendor id to connect\n");
	printf(" -p <pid>   use this product id to connect\n");
}

int	main(int argc, char *argv[]) {
	// parse command line
	int	c;
	int	debug = 0;
	uint16_t	vid = 0xf055;
	uint16_t	pid = 0x1234;
	while (EOF != (c = getopt(argc, argv, "dh?v:p:V")))
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
		rc = libusb_control_transfer(handle,
			LIBUSB_REQUEST_TYPE_VENDOR |
			LIBUSB_RECIPIENT_DEVICE |
			LIBUSB_ENDPOINT_OUT, GUIDERPORT_SET_ALL_TIMES, 
			value, index, (void *)porttimes, 8, 1000);
		if (rc < 0) {
			fprintf(stderr, "cannot send SET_ALL_TIMES: %s (%d)\n", 
				libusb_strerror(rc), rc);
			return EXIT_FAILURE;
		}
		if (8 != rc) {
			fprintf(stderr, "cannot send all bytes\n");
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
