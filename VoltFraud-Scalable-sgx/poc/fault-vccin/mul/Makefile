# try to do some autodetecting
UNAME := $(shell uname -s)

ifeq "$(UNAME)" "Darwin"
	OS=macosx
endif
ifeq "$(OS)" "Windows_NT"
	OS=windows
endif
ifeq "$(UNAME)" "Linux"
	OS=linux
endif


#################  Mac OS X  ##################################################
ifeq "$(OS)" "macosx"

EXE_SUFFIX=

ARCHS=   -arch i386 -arch x86_64
CFLAGS+= $(ARCHS)
CFLAGS += -mmacosx-version-min=10.6
CFLAGS_MONGOOSE=  -I./mongoose -pthread -g 
LIBS+=	 $(ARCHS)

endif

#################  Windows  ##################################################
ifeq "$(OS)" "windows"

EXE_SUFFIX=.exe

CFLAGS_MONGOOSE = -I./mongoose -mthreads

endif


#################  Common  ##################################################
#export TRIGGER_SEL = -D TRIGGER_TEENSY
export TRIGGER_SEL = -D TRIGGER_DTR

HWLIB_DIR=../../lib/
VISA_PATH = /usr/include/ni-visa
LIB_VOLT = $(HWLIB_DIR)

INCLUDES	+= -I $(LIB_VOLT) -I$(VISA_PATH)
LDLIBS		+= -L $(LIB_VOLT)
LDFLAGS		+= -pthread -lDCbias
CFLAGS = $(TRIGGER_SEL) $(INCLUDES) $(LDLIBS) $(LIBS) -O0 -Wall -mrdrnd

all: glitch_controller

lib:
	$(info -----Building hwvolt library-----)
	$(MAKE) -C $(HWLIB_DIR)

glitch_controller: lib glitch_controller.c target_functions.c
	$(info -----Building glitch_controller-----)
	$(CC) $(CFLAGS) -std=gnu99 -c target_functions.c -o target_functions.a
	$(CC) $(CFLAGS) -o glitch_controller$(EXE_SUFFIX) glitch_controller.c *.a  $(LDFLAGS)

clean:
	$(MAKE) -C $(HWLIB_DIR) clean
	rm -f $(OBJ) glitch_controller glitch_controller.exe *.o *.a
	rm -f $(LIB_ARDUINO_SC)mongoose/mongoose.o
	rm -f *.s
	rm -f target_functions

test: target_functions.c target_functions.h lib
	$(CC) $(CFLAGS) -std=gnu99 -D TEST_TARGET -o target_functions target_functions.c -lplundervolt
	# Generate assembly file
	$(CC) $(CFLAGS) -std=gnu99 -D TEST_TARGET -S target_functions.c

