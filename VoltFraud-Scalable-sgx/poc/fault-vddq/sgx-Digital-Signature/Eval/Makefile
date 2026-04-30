CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lcrypto

TARGET = verify
SRC = verify.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)