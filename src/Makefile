CROSS = arm-none-linux-gnueabi-

CC = $(CROSS)gcc
AR = $(CROSS)ar

CFLAGS = -shared -fPIC

CPPFLAGS := -I../inc

OBJ := bmp.o ts.o audio.o

libcommon.so:$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	mv $@ ../lib

$(OBJ):%.o:%.c
	$(CC) $< -o $@ $(CPPFLAGS) -c
	
clean:
	$(RM) $(OBJ)
