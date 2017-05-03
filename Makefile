vpath %.c = source/
vpath %.h = inlcude/

SRCPATH = ./source

SRC := $(wildcard source/*.c)
OBJ := $(SRC:%.c=%.o)
OBJ := $(filter-out source/piano.o, $(OBJ))

CROSS = arm-none-linux-gnueabi

CC = $(CROSS)-gcc

CPPFLAGS += -I ./include
#CPPFLAGS += -DDEBUG

LDFLAGS  += -L ./lib
LDFLAGS  += -lcommon
LDFLAGS  += -lpthread
LDFLAGS  += -Wl,-rpath=./lib

all:piano

piano:piano.c
	$(MAKE) -C $(SRCPATH)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJ) piano .*.sw?

distclean:clean
	$(RM) ./lib/*
