#export TRIGGER_SEL = -D TRIGGER_TEENSY
export TRIGGER_SEL = -D TRIGGER_DTR

HWLIB_DIR	=../../../lib/
LIB_VOLT	= $(HWLIB_DIR)
VISA_PATH = /usr/include/ni-visa
# INCLUDE		+= -I $(LIB_VOLT) -I$(VISA_PATH)
LDLIBS		+= -L$(LIB_VOLT) -L/usr/lib/x86_64-linux-gnu/
# LDFLAGS		+= $(TRIGGER_SEL) $(INCLUDE) -pthread -lvisa -lDCbias

ifeq ($(SGX_SDK),)
    SGX_SDK          = /opt/intel/sgxsdk
endif
export SGX_SDK




ENCLAVE              = Enclave
SUBDIRS              = $(ENCLAVE)

CC                   = gcc
AS                   = gcc
LD                   = gcc

ifeq ($(M32), 1)
	CFLAGS   += -m32 -DM32=$(M32)
	LDFLAGS  += -m32
else
	LIB_SUFX = 64
endif

CFLAGS              += $(TRIGGER_SEL) -fPIC -fno-stack-protector -fno-builtin -fno-jump-tables \
                       -fno-common -Wno-attributes -g -D_GNU_SOURCE -O0 -mavx2 -I$(LIB_VOLT) -I$(VISA_PATH)
INCLUDE             += -I$(SGX_SDK)/include/
LDFLAGS             += -lencl_proxy -lsgx_urts \
                       -lsgx_uae_service $(SUBDIRS:%=-L %) -L$(SGX_SDK)/lib$(LIB_SUFX)/ \
                       $(LDLIBS) -lDCbias -pthread -lcrypto

SOURCES              = $(shell ls *.c)
OBJECTS              = $(SOURCES:.c=.o)
OUTPUT               = app

BUILDDIRS            = $(SUBDIRS:%=build-%)
CLEANDIRS            = $(SUBDIRS:%=clean-%)

.SILENT:
all: $(OUTPUT)
	
run: clean all
	sudo ./$(OUTPUT) ${ARGS}

debug: clean all
	sudo `which sgx-gdb` ./$(OUTPUT)

lib:
	$(info -----Building hwvolt library-----)
	$(MAKE) -C $(HWLIB_DIR)

$(OUTPUT): $(BUILDDIRS) $(OBJECTS) lib
	echo "$(INDENT)[LD]" $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)
	$(LD) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

%.o : %.c
	echo "$(INDENT)[CC] " $<
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

%.o : %.S
	echo "$(INDENT)[AS] " $<
	$(AS) $(INCLUDE) -c $< -o $@

clean: $(CLEANDIRS)
	echo "$(INDENT)[RM]" $(OBJECTS) $(OUTPUT)
	rm -f $(OBJECTS) $(OUTPUT)
	$(MAKE) -C ./Enclave clean
	$(MAKE) -C $(HWLIB_DIR) clean

$(BUILDDIRS):
	echo "$(INDENT)[===] $(@:build-%=%) [===]"
	$(MAKE) -C $(@:build-%=%) INDENT+="$(INDENT_STEP)" M32=$(M32) curr-dir=$(curr-dir)/$(@:build-%=%)

$(CLEANDIRS):
	echo "$(INDENT)[===] $(@:clean-%=%) [===]"
	$(MAKE) clean -C $(@:clean-%=%) INDENT+="$(INDENT_STEP)" curr-dir=$(curr-dir)/$(@:build-%=%)
