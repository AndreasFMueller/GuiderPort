/*
 * guiderport.c -- main function of the guiderport firmware
 *
 * (c) 2015 Prof Dr Andreas Müller, Hochschule Rapperswil
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#include <port.h>
#include <timer.h>
#include <LUFA/Platform/Platform.h>
#include <LUFA/Drivers/USB/USB.h>
#include <avr/wdt.h>

int	main(int argc, char *argv[]) {
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 4; i++) {
			port_value(i, 1);
			_delay_ms(100);
			port_value(i, 0);
		}
		port_value(2, 1);
		_delay_ms(100);
		port_value(2, 0);
		port_value(1, 1);
		_delay_ms(100);
		port_value(1, 0);
	}
	USB_Init(USB_DEVICE_OPT_FULLSPEED);
	timer_start();
	GlobalInterruptEnable();
	for (;;) {
	}
}

void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));

void wdt_init(void) {
	MCUSR = 0;
	wdt_disable();
}
