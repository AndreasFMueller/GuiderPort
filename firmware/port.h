/*
 * port.h -- interface to the port pins
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _port_h
#define _port_h

typedef unsigned short porttimes_t[4];

extern void	port_on(unsigned char port);
extern void	port_off(unsigned char port);
extern void	port_value(unsigned char port, unsigned char value);

extern void	port_set(unsigned char port, unsigned short value);
extern void	port_set_all(const porttimes_t ports);
extern void	port_step(unsigned short step);

#endif /* _port_h */
