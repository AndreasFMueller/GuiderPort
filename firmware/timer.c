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

/**
 * \brief Timer initialization
 *
 * This function initializes the timer to interrupt 100 times per second.
 * The output compare match register A of timer1 of the AT90USB162 is used
 * to get this resolution.
 *
 * It has the constructor attribute which ensures that it is called in
 * the initialization sequence even before main is called.
 */
static void	timer_setup() {
	// initialize the timer
	TCNT1 = 0;
	OCR1A = 10000;
	TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << WGM11) | (0 << WGM10);
	TCCR1B = (0 << WGM13) | (1 << WGM12) |
			(0 << CS12) | (0 << CS11) | (1 << CS10);
}

/**
 * \brief Enable timer
 *
 * This enables timer interrupts and sets the watchdog timer to 1 second.
 * The timer interrupt resets the watchdog.
 */
void	timer_start() {
	TIMSK1 |= _BV(OCIE1A);
	wdt_enable(WDTO_1S);
}

/**
 * \brief Stop the timer
 *
 * This disables timer interrupts and stops the whatchdog. Note that
 * no other interrupts are disabled, so USB continues to run.
 */
void	timer_stop() {
	TIMSK1 &= ~_BV(OCIE1A);
	wdt_disable();
}

/**
 * \brief Timer interrupt handler
 *
 * The interrupt handler resets the watchdog timer and counts the
 * port timers down 1 unit (10ms)
 */
ISR(TIMER1_COMPA_vect) {
	wdt_reset();
	port_step(1);
}
