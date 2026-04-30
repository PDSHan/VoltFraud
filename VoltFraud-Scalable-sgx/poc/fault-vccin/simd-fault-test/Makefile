CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -std=c11 -mavx2
TARGET := simd_fault_test
SRC := simd_fault_test.c
HWLIB_DIR := ../../../lib

INCLUDES := -I$(HWLIB_DIR)
EXTRA_SRC := $(HWLIB_DIR)/DCbias.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(SRC) $(EXTRA_SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
