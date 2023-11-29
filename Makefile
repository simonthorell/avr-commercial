# Tool Definitions (Linux, Mac & Windows)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CC=avr-g++
    OBJCOPY=avr-objcopy
    OBJDUMP=avr-objdump
    AVRSIZE=avr-size
    OBJISP=avrdude
    PORT=/dev/ttyUSB0 # Adjust as necessary
endif
ifeq ($(UNAME_S),Darwin)
    CC=avr-g++
    OBJCOPY=avr-objcopy
    OBJDUMP=avr-objdump
    AVRSIZE=avr-size
    OBJISP=avrdude
    PORT=/dev/tty.usbmodem # Adjust as necessary
endif
ifeq ($(OS),Windows_NT)
    CC=C:\avr\bin\avr-g++
    OBJCOPY="C:\avr\bin\avr-objcopy"
    OBJDUMP="C:\avr\bin\avr-objdump"
    AVRSIZE="C:\avr\bin\avr-size"
    OBJISP="C:\avr\bin\avrdude"
    PORT=\\\\.\\COM3 # Adjust as necessary
endif

MCU=atmega328p
CFLAGS=-Wall -Wextra -Wundef -pedantic \
        -Os -std=c++11 -DF_CPU=16000000UL -mmcu=$(MCU) -DBAUD=19200 -Iinclude
LDFLAGS=-mmcu=$(MCU)
BIN=avr-commercial
OUT=bin/$(BIN).hex
SRC_DIR=src
INCLUDE_DIR=include
OBJ_DIR=obj

# Output directory
APP_DIR=app
BIN=avr-commercial
ELF_OUT=$(APP_DIR)/$(BIN).elf
OUT=$(APP_DIR)/$(BIN).hex

# Source and Object Files
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
HEADERS=$(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS=$(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o)))

# Debug/Release Output Directory
DEBUG?=1
ifeq ($(DEBUG), 1)
    OUTPUTDIR=$(APP_DIR)/debug
else
    OUTPUTDIR=$(APP_DIR)/release
endif

# Default target
all: $(OUT)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(ELF_OUT): $(OBJECTS)
	@mkdir -p $(APP_DIR)
	$(CC) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

# Hex
$(OUT): $(ELF_OUT)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# ISP
isp: $(OUT)
	$(OBJISP) -F -V -c arduino -p $(MCU) -P $(PORT) -U flash:w:$<

# Clean
clean:
	rm -f $(OBJ_DIR)/*.o $(ELF_OUT) $(OUT)
	rm -rf $(APP_DIR) $(OBJ_DIR)

# Phony Targets
.PHONY: all clean isp