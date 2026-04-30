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

HWLIB_DIR=../../../lib/
VISA_PATH = /usr/include/ni-visa
LIB_VOLT = $(HWLIB_DIR)

INCLUDES	+= -I$(LIB_VOLT) -I$(VISA_PATH)
LDLIBS		+= -L $(LIB_VOLT)
LDFLAGS		+= -pthread -lDCbias
CFLAGS = $(TRIGGER_SEL) $(INCLUDES) $(LDLIBS) $(LIBS)  -march=native  -O0 -Wall -mrdrnd

all: memory_test

lib:
	$(info -----Building hwvolt library-----)
	$(MAKE) -C $(HWLIB_DIR)

memory_test: lib memory_test.c
	$(info -----Building memory_test-----)
	$(CC) $(CFLAGS) -o memory_test$(EXE_SUFFIX) memory_test.c  $(LDFLAGS)

clean:
	$(MAKE) -C $(HWLIB_DIR) clean
	rm -f $(OBJ) test memory_test.exe *.o *.a
	rm -f *.s
	rm -f target_functions

