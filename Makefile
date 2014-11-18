#This is a makefile for Blink.c
#Use "make all" to compile and link
#Use "make load" to download to MCU
#Use "make dump" to dissasemble the binary and see the size of different
#sections
#Use "make map" to have the linker generate a map file

# General Options
PROG=dimmer
SOURCES=ATmega88A_TWI.c LCD_TWIinterface.c joystick_ADC.c DimmerMain.c LED_debug.c LED_PWM.c
OBJECTS=ATmega88A_TWI.o LCD_TWIinterface.o joystick_ADC.o DimmerMain.o LED_debug.o LED_PWM.o

# Compiler and Linker options
GCC=gcc
CFLAGS=-Os -Wall -c
LFLAGS=-Wall

# Include directories
INC=-I/

all:$(PROG).elf
	avr-size $(PROG).elf
	avr-objcopy -j .text -j .data -O ihex $(PROG).elf $(PROG).hex

$(PROG).elf:$(OBJECTS)
	$(GCC) $(LFLAGS) -o $(PROG).elf $(OBJECTS)

$(OBJECTS):$(SOURCES)
	avr-gcc $(CFLAGS) $(SOURCES)

load:
	atprogram -t $(PROGRAMMER) -i $(PROGTYPE) -d $(PROGMCU) program -c -fl -f $(PROG).hex	

dump:$(PROG).elf
	avr-objdump -h -S $(PROG).elf > $(PROG).lst	

clean:
	rm $(PROG).elf $(PROG).hex $(OBJECTS)
