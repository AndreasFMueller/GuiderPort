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


void	port_setup(void) __attribute__ ((constructor));

static porttimes_t	ports;

#define	PORT_ON(p)	do { PORTD &= ~(1 << p); } while (0)
#define	PORT_OFF(p)	do { PORTD |= (1 << p); } while (0)
#define PORT_GET(p)	((PORTD & (1 << p)) ? 0 : 1)

/**
 * \brief Turn port on
 *
 * Turn on the port indicated by the port number in argument port
 *
 * \param port	number of the port 0-3
 */
void	port_on(unsigned char port) {
	PORT_ON(port);
}

/**
 * \brief Turn port off
 *
 * Turn off the port indicated by the port number in argument port
 *
 * \param port	number of the port 0-3
 */
void	port_off(unsigned char port) {
	PORT_OFF(port);
}

/**
 * \brief Set the value of a port
 *
 * Set an output to a given value. If value is zero, then the port is
 * turned off, if it is nonzero, it is turned on.
 *
 * \param port		port number
 * \param value		whether the port should be on or off
 */
void	port_value(unsigned char port, unsigned char value) {
	if (value) {
		PORT_ON(port);
	} else {
		PORT_OFF(port);
	}
}

/**
 * \brief Get the state of a port
 *
 * Read the state of the output with number port
 *
 * \param port	number of the port 0-3
 */
unsigned char	port_get(unsigned char port) {
	return PORT_GET(port);
}

/**
 * \brief Retrieve all port values
 *
 * This function reads the current state of all ports and collects it in
 * a single unsigned char.
 */
unsigned char	port_get_all() {
	unsigned char	result = 0;
	for (unsigned char port = 0; port < 4; port++) {
		result |= port_get(port) ? (1 << port) : 0;
	}
	return result;
}

/**
 * \brief Port setup
 *
 * This function configures the IO-pins D0-D3 as outputs and turns them off.
 * This method has the constructor attribute, which ensures that it is
 * called automatically during startup.
 */
void	port_setup(void) {
	// initialize ports
	PORTD |= (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3);
	DDRD  |= (1 << DDD0)   | (1 << DDD1)   | (1 << DDD2)   | (1 << DDD3);

	// turn of outputs and reset timers
	for (unsigned char i = 0; i < 4; i++) {
		port_value(i, 0);
		ports[i] = 0;
	}
}

/**
 * \brief Set time value for a port
 *
 * This function sets/overwrites the time during which the port selected
 * by the port argument should be turned on. 
 *
 * \param port		port number 0-3
 * \param value		time in 10ms intervals
 */
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

/**
 * \brief Set all port times
 *
 * This function sets the port time for all ports. It is used by the
 * implementation of the SET_ALL_TIMES request.
 *
 * \param p	array containing on times for all ports
 */
void	port_set_all(const porttimes_t p) {
	for (unsigned char i = 0; i < 4; i++) {
		port_set(i, p[i]);
	}
}

/**
 * \brief Perform a timer step 
 *
 * This function is called from the timer interrupt to count down the 
 * timer values of the ports.
 */
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
