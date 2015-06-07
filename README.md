GuiderPort

Most cameras for astrophotography have a guider port for autoguiding.
However, this is a really bad arrangment, because it requires an
additional cable between the telescope and the mount, adding an
additional force that could contribute to telescope flex. This
project offers the hard and software for a standalone guider port
attached to a host computer via USB. This eliminates the need for
a guider port on the camera, and the guider port ist now directly
connected to the guiding computer.

The hardware uses an USB enable AVR microcontroller AT90USB162, but
an AT90USB82 is also sufficient. The schematics and board files in
KiCAD format are contained in the firmware directory. A suitable case
for the guider port hardware can be 3D-printed from the files in the
case subdirectory.

The firmware is based on the LUFA library. avr-gcc and avr-libc are
also needed to compile it. The Makefile contains targets to program
it using the avrispmk2 programmer and avrdude.

The client directory contains a libusb based client to test the
device.

