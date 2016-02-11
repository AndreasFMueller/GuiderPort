/*
 * event.h -- function to handle USB events
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _event_h
#define _event_h

#include <LUFA/Drivers/USB/USB.h>

/**
 * \brief Command codes for the GuiderPort commands
 *
 * A description of the commands is given in event.c where the
 * commands are implemented.
 */
#define	GUIDERPORT_RESET		0
#define	GUIDERPORT_SET			1
#define GUIDERPORT_SET_PORT_TIME	2
#define GUIDERPORT_SET_ALL_TIMES	3
#define GUIDERPORT_GET			4
#define GUIDERPORT_SERIAL		5

/**
 * \brief Event handle for control requests
 *
 * This function is called when a control request arrives at the device.
 * It implements the four commands understood by the device. Note that
 * this function must be linked, and sometimes the -u linker option is
 * needed to force the linker to do that.
 */
extern void	EVENT_USB_Device_ControlRequest();

#endif /* _event_h */
