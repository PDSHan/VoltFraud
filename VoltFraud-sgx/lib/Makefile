INCLUDES	+= -I$(VISA_PATH)
LDFLAGS		+= -lvisa

CFLAGS = -O0 -Wall -mrdrnd -std=gnu99 $(INCLUDES)

all: libhwvolt libplundervolt

libhwvolt: DCbias.c DCbias.h
	$(CC) $(CFLAGS) -std=gnu99 -c DCbias.c -o libDCbias.a $(LDFLAGS)

libplundervolt: plundervolt.c plundervolt.h
	$(CC) $(CFLAGS) -std=gnu99 -c plundervolt.c -o libplundervolt.a

clean:
	rm -f $(OBJ) *.o *.a
	rm -f *.s

