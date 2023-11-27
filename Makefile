# Tool Definitions
CC=/opt/homebrew/bin/avr-gcc
LD=/opt/homebrew/bin/avr-ld
OBJCOPY=/opt/homebrew/bin/avr-objcopy
OBJDUMP=/opt/homebrew/bin/avr-objdump
AVRSIZE=/opt/homebrew/bin/avr-size
OBJISP=/opt/homebrew/bin/avrdude
MCU=atmega328p
CFLAGS=-Wall -Wextra -Wundef -pedantic \
        -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=$(MCU) -DBAUD=19200
LDFLAGS=-mmcu=$(MCU)
PORT=/dev/ttyACM0 # Update this with your port
BIN=helloarduino
OUT=${BIN}.hex
SOURCES = main.cpp

DEBUG?=1

ifeq ($(DEBUG), 1)
	OUTPUTDIR=bin/debug
else
	OUTPUTDIR=bin/release
endif

OBJS =  $(addprefix $(OUTPUTDIR)/,$(SOURCES:.cpp=.o))

all: $(OUTPUTDIR)  $(OUT) 

$(OBJS): Makefile

$(OUTPUTDIR)/%.o:%.cpp
	$(CC) $(CFLAGS) -MD -o $@ -c $<

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@


$(OBJS):$(SOURCES)

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: ${BIN}.hex
	$(OBJISP) -F -V -c arduino -p ${MCU} -P ${PORT} -U flash:w:$<


clean:
	del "$(OUT)"  *.map *.P *.d

# $(OUTPUTDIR): 
# 	@mkdir "$(OUTPUTDIR)"

$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)

.PHONY: clean dirs
