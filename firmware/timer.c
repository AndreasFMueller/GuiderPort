/*
 * timer.c -- timer implementation
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#include <timer.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/wdt.h>
#include <port.h>

static void     timer_setup() __attribute__ ((constructor));

static void	timer_setup() {
	// initialize the timer
	TCNT1 = 0;
	OCR1A = 10000;
	TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << WGM11) | (0 << WGM10);
	TCCR1B = (0 << WGM13) | (1 << WGM12) |
			(0 << CS12) | (0 << CS11) | (1 << CS10);
}

void	timer_start() {
	TIMSK1 |= _BV(OCIE1A);
	wdt_enable(WDTO_1S);
}

void	timer_stop() {
	TIMSK1 &= ~_BV(OCIE1A);
	wdt_disable();
}

ISR(TIMER1_COMPA_vect) {
	wdt_reset();
	port_step(1);
}
