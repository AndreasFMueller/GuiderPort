/*
 * event.c -- enable event handling
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#include <event.h>
#include <port.h>
#include <LUFA/Drivers/USB/Core/Events.h>
#include <avr/wdt.h>

void	process_reset() {
	Endpoint_ClearSETUP();
	Endpoint_ClearStatusStage();
	wdt_enable(WDTO_15MS);
}

void	process_set() {
	Endpoint_ClearSETUP();
	Endpoint_ClearStatusStage();
	for (unsigned char i = 0; i < 4; i++) {
		if (USB_ControlRequest.wIndex & (1 << i)) {
			port_value(i, USB_ControlRequest.wValue & (1 << i));
		}
	}
}

void	process_set_port_time() {
	Endpoint_ClearSETUP();
	Endpoint_ClearStatusStage();
	port_set(USB_ControlRequest.wIndex & 0x3, USB_ControlRequest.wValue);
}

porttimes_t	newports;

void	process_set_all_times() {
	Endpoint_ClearSETUP();
	Endpoint_Read_Control_Stream_LE((void *)newports, 8);
	Endpoint_ClearIN();
	port_set_all(newports);
}

#define	is_control() \
	((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_TYPE) 	\
		== REQTYPE_VENDOR) 					\
	&&								\
	((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_RECIPIENT)\
		== REQREC_DEVICE)

#define	is_incoming() \
	((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_DIRECTION)	\
		== REQDIR_HOSTTODEVICE)

void	EVENT_USB_Device_ControlRequest() {
	if (is_control()) {
		if (is_incoming()) {
			switch (USB_ControlRequest.bRequest) {
			case GUIDERPORT_RESET:
				process_reset();
				break;
			case GUIDERPORT_SET:
				process_set();
				break;
			case GUIDERPORT_SET_PORT_TIME:
				process_set_port_time();
				break;
			case GUIDERPORT_SET_ALL_TIMES:
				process_set_all_times();
				break;
			}
		}
	}
}

