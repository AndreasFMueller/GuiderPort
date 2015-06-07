/*
 * port.c -- implementation of the port interface
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#include <avr/io.h>
#include <util/atomic.h>
#include <port.h>

#define	RAPLUS		PORTD0
#define RAMINUS		PORTD1
#define DECPLUS		PORTD2
#define	DECMINUS	PORTD3
#define	GPORT		PORTD

void	port_setup(void) __attribute__ ((constructor));

static porttimes_t	ports;

#define	PORT_ON(p)	do { GPORT &= ~(1 << p); } while (0)
#define	PORT_OFF(p)	do { GPORT |= (1 << p); } while (0)

void	port_on(unsigned char port) {
	PORT_ON(port);
}

void	port_off(unsigned char port) {
	PORT_OFF(port);
}

void	port_value(unsigned char port, unsigned char value) {
	if (value) {
		PORT_ON(port);
	} else {
		PORT_OFF(port);
	}
}

void	port_setup(void) {
	// initialize ports
	PORTD |= (1 << RAPLUS) | (1 << RAMINUS) |
			(1 << DECPLUS) | (1 << DECMINUS);
	DDRD |= (1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3);

	// reset timers
	for (unsigned char i = 0; i < 4; i++) {
		port_value(i, 0);
		ports[i] = 0;
	}
}

void	port_set(unsigned char i, unsigned short value) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if (0 == value) {
			if (0 != ports[i]) {
				port_off(i);
			}
			ports[i] = 0;
		} else {
			if (0 == ports[i]) {
				port_on(i);
			}
			ports[i] = value;
		}
	}
}

void	port_set_all(const porttimes_t p) {
	for (unsigned char i = 0; i < 4; i++) {
		port_set(i, p[i]);
	}
}

void	port_step(unsigned short delta) {
	// check whether to turn off the raplus port
	for (unsigned char i = 0; i < 4; i++) {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			if (ports[i] > delta) {
				ports[i] -= delta;
			} else {
				if (0 != ports[i]) {
					port_off(i);
				}
				ports[i] = 0;
			}
		}
	}
}
