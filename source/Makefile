CROSS = arm-none-linux-gnueabi
CC = $(CROSS)-gcc
AR = $(CROSS)-ar

CFLAGS = -shared -fPIC

CPPFLAGS := -I ../include

OBJ := bmp.o ts.o audio.o

all:libcommon.so
	mv $^ ../lib

libcommon.so:$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ):%.o:%.c
	$(CC) $< -o $@ $(CPPFLAGS) -c
