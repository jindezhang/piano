vpath %.c = src/
vpath %.h = inc/

SRCPATH = ./src

HEADER := $(wildcard inc/*.h)
SRC := $(wildcard src/*.c)
OBJ := $(SRC:%.c=%.o)
OBJ := $(filter-out src/piano.o, $(OBJ))

CROSS = arm-none-linux-gnueabi-

CC = $(CROSS)gcc

CPPFLAGS += -Iinc
#CPPFLAGS += -DDEBUG

LDFLAGS += -Llib
LDFLAGS += -lcommon
LDFLAGS += -lpthread
LDFLAGS += -Wl,-rpath=./lib
LDFLAGS += -Wl,-rpath=.

all:piano

piano:$(SRC) $(HEADER)
	$(MAKE) -C $(SRCPATH)
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJ) piano .*.sw?

distclean:clean
	$(RM) ./lib/* ./src/*.o
