CC = gcc

SRC = button.c
TARGET = button

CFLAGS=`pkg-config --cflags glib-2.0`
LDFLAGS=`pkg-config --libs glib-2.0`
LDFLAGS+=-lgattlib
LDFLAGS+=-lpaho-mqtt3c

all: $(SRC)
	$(CC) -Wall $(SRC) $(CFLAGS) -o $(TARGET) $(LDFLAGS)
