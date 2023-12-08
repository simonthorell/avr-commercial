# Makefile for AVR programming with testing using simavr

# Define MKDIR command based on the OS
ifeq ($(OS),Windows_NT)
    MKDIR=if not exist "$(1)" mkdir "$(1)"
else
    MKDIR=mkdir -p $(1)
endif

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

# Libraries directory
LIBS_DIR=libs
CFLAGS += -I$(LIBS_DIR)

# Source and Object Directories
SRC_DIR=src
INCLUDE_DIR=include
OBJ_DIR=obj
LIBS_SRC=$(wildcard $(LIBS_DIR)/*.cpp) # Assuming your library files are .cpp

# Output directory
APP_DIR=app
BIN=avr-commercial
ELF_OUT=$(APP_DIR)/$(BIN).elf
OUT=$(APP_DIR)/$(BIN).hex

# Source and Object Files
SOURCES=$(wildcard $(SRC_DIR)/*.cpp) $(LIBS_SRC)
HEADERS=$(wildcard $(INCLUDE_DIR)/*.h) $(wildcard $(LIBS_DIR)/*.h)
OBJECTS=$(addprefix $(OBJ_DIR)/,$(notdir $(SOURCES:.cpp=.o)))

# Test Source and Object Directories
TEST_DIR=tests
OBJ_TEST_DIR=obj_test

# Test Source and Object Files
TEST_SOURCES=$(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS=$(addprefix $(OBJ_TEST_DIR)/,$(notdir $(TEST_SOURCES:.cpp=.o)))

# Test Executable Output
TEST_BIN=test-avr-commercial
TEST_OUT=$(APP_DIR)/$(TEST_BIN).elf

# Debug/Release Output Directory
DEBUG?=1
ifeq ($(DEBUG), 1)
    OUTPUTDIR=$(APP_DIR)/debug
else
    OUTPUTDIR=$(APP_DIR)/release
endif

# Phony Targets
.PHONY: all test clean isp

# Default target
all: $(OUT)

# Test target
test: $(TEST_OBJECTS)
	@$(call MKDIR,$(APP_DIR))
	$(CC) $(LDFLAGS) -o $(TEST_OUT) $^
	$(AVRSIZE) $(TEST_OUT)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) $(LIBS_SRC)
	@$(call MKDIR,$(OBJ_DIR))
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for compiling library sources
$(OBJ_DIR)/%.o: $(LIBS_DIR)/%.cpp $(HEADERS)
	@$(call MKDIR,$(OBJ_DIR))
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Test Sources
$(OBJ_TEST_DIR)/%.o: $(TEST_DIR)/%.cpp $(HEADERS)
	@$(call MKDIR,$(OBJ_TEST_DIR))
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(ELF_OUT): $(OBJECTS)
	@$(call MKDIR,$(APP_DIR))
	$(CC) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

# Link Test Executable
$(TEST_OUT): $(TEST_OBJECTS) $(OBJECTS) # Assuming tests may use the main object files
	@$(call MKDIR,$(APP_DIR))
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
	rm -f $(OBJ_DIR)/*.o $(OBJ_TEST_DIR)/*.o $(ELF_OUT) $(OUT) $(TEST_OUT)
	rm -rf $(APP_DIR) $(OBJ_DIR) $(OBJ_TEST_DIR)