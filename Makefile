# Tool Definitions
CC=avr-g++
OBJCOPY=avr-objcopy
MCU=atmega328p
CFLAGS=-Wall -Wextra -Wundef -pedantic \
        -Os -std=c++11 -DF_CPU=16000000UL -mmcu=$(MCU) -DBAUD=19200 -Iinclude
LDFLAGS=-mmcu=$(MCU)
BIN=avr-commercial
APP_DIR=app
OUT=$(APP_DIR)/$(BIN).hex
SRC_DIR=src
INCLUDE_DIR=include
OBJ_DIR=obj

# Source and Object Files
SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o)))

# Default target
all: $(OUT)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(APP_DIR)/$(BIN).elf: $(OBJECTS)
	@mkdir -p $(APP_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Hex
$(OUT): $(APP_DIR)/$(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Clean
clean:
	rm -f $(OBJ_DIR)/*.o $(APP_DIR)/$(BIN).elf $(OUT)
	rm -rf $(APP_DIR) $(OBJ_DIR)

# Phony Targets
.PHONY: all clean
