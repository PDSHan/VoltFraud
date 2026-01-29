INCLUDES	+= -I$(VISA_PATH)
LDFLAGS		+= -lvisa

CFLAGS = -O0 -Wall -mrdrnd -std=gnu99 $(INCLUDES)

all: libvolt

libvolt: DCbias.c DCbias.h
	$(CC) $(CFLAGS) -std=gnu99 -c DCbias.c -o libDCbias.a $(LDFLAGS)

clean:
	rm -f $(OBJ) *.o *.a
	rm -f *.s

