/*
 * event.h -- function to handle USB events
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _event_h
#define _event_h

#include <LUFA/Drivers/USB/USB.h>

#define	GUIDERPORT_RESET		0
#define	GUIDERPORT_SET			1
#define GUIDERPORT_SET_PORT_TIME	2
#define GUIDERPORT_SET_ALL_TIMES	3

extern void	EVENT_USB_Device_ControlRequest();

#endif /* _event_h */
