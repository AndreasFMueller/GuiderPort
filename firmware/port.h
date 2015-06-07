/*
 * port.h -- interface to the port pins
 *
 * (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _port_h
#define _port_h

/**
 * \brief Port timer array
 *
 * The values in this array indicate for how many intervals of 10ms the
 * ports should be turned on (active low).
 */
typedef unsigned short porttimes_t[4];

extern void	port_on(unsigned char port);
extern void	port_off(unsigned char port);
extern void	port_value(unsigned char port, unsigned char value);
extern unsigned char	port_get(unsigned char port);
extern unsigned char	port_get_all();

extern void	port_set(unsigned char port, unsigned short value);
extern void	port_set_all(const porttimes_t ports);
extern void	port_step(unsigned short step);

#endif /* _port_h */
