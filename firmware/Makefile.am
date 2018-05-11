#
# Makefile.am -- build the software for the guiderport
#
# (c) 2015 Prof Dr Andreas Mueller, Hochschule Rapperswil
#
# LUFA configuration stuff
MCU = @LUFA_MCU@
ARCH = @LUFA_ARCH@
F_USB = @LUFA_F_USB@
F_CPU = @LUFA_F_CPU@

AUTOMAKE_OPTIONS = subdir-objects

# Construct LUFA module source variables
LUFA_SRC_USB_COMMON = \
	@LUFA_PATH@/LUFA/Drivers/USB/Core/AVR8/USBController_AVR8.c	\
	@LUFA_PATH@/LUFA/Drivers/USB/Core/AVR8/USBInterrupt_AVR8.c	\
	@LUFA_PATH@/LUFA/Drivers/USB/Core/ConfigDescriptors.c		\
	@LUFA_PATH@/LUFA/Drivers/USB/Core/Events.c			\
	@LUFA_PATH@/LUFA/Drivers/USB/Core/USBTask.c			\
	@LUFA_PATH@/LUFA/Drivers/USB/Class/Common/HIDParser.c

LUFA_SRC_USB_DEVICE = \
	@LUFA_PATH@/LUFA/Drivers/USB/Core/AVR8/Device_AVR8.c		\
	@LUFA_PATH@/LUFA/Drivers/USB/Core/AVR8/Endpoint_AVR8.c		\
	@LUFA_PATH@/LUFA/Drivers/USB/Core/AVR8/EndpointStream_AVR8.c	\
	@LUFA_PATH@/LUFA/Drivers/USB/Core/DeviceStandardReq.c		\
	$(LUFA_SRC_USB_COMMON)

noinst_PROGRAMS = guiderport

AVRDUDE = avrdude -v -p usb162 -b 115200 -c avrispmkII -P usb

flash:	guiderport.hex guiderport.eeprom
	$(AVRDUDE) -U flash:w:guiderport.hex -U eeprom:w:guiderport.eeprom

guiderport.hex: guiderport
	avr-objcopy --remove-section=.eeprom --target=ihex guiderport \
		guiderport.hex
guiderport.eeprom: guiderport
	avr-objcopy --only-section=.eeprom --target=ihex \
		--change-section-lma .eeprom=0 \
		guiderport guiderport.eeprom

lib_LTLIBRARIES = libguiderport.la

noinst_HEADERS = port.h timer.h descriptor.h descriptor.h event.h serial.h

libguiderport_la_SOURCES = port.c timer.c descriptor.c event.c serial.c \
	$(LUFA_SRC_USB_DEVICE)

guiderport_SOURCES = guiderport.c
guiderport_DEPENDENCIES = libguiderport.la
guiderport_LDFLAGS = -lguiderport

# setting the fuse values
# low fuse byte
# -------------
# CKDIV8        = 0             Clock divided by 8 (yes)
# CKOUT         =  1            Clock out enabled (no)
# SUT1..0       =   10          Startup time setting (fast rising power)
# CKSEL3..0     =     1111      Clock source setting (8 MHz crystal)
#                 ________
#                 01101111      = 0x6f
#
#
# high fuse byte
# --------------
# DWEN          = 1             DebugWIRE enabled (no)
# RSTDSBL       =  1            external reset disabled (no)
# SPIEN         =   0           Serial program and data download enabled (yes)
# WDTON         =    1          Watchdog timer always on (no)
# EESAVE        =     0         EEPROM preserved on chip erase (yes)
# BOOTSZ1..0    =      00       Select Boot size
# BOOTRST       =        1      Reset vector @0x0000
#                 ________
#                 11010001      = 0xd1
#
#
# extended fuse byte
# ------------------
# unused        = 1111          (reserved)
# HWBE          =     0         
# BODLEVEL2..0  =      111      Brown-out Detector trigger level (disabled)
#                 ________
#                 11110111      = 0xf7
#
# original fuse settings reported by avrdude
# lfuse reads as 5E
# hfuse reads as D9
# efuse reads as F4

fuses:
	$(AVRDUDE) -U lfuse:w:0x6f:m -U hfuse:w:0xd1:m -U efuse:w:0xf7:m

read:   readback.hex

readback.hex:
	$(AVRDUDE) -U flash:r:readback.hex

read:
	$(AVRDUDE) -U eeprom:r:eeprom.raw:r -u

size:   guiderport
	avr-size *.o guiderport

