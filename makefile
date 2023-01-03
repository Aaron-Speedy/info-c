CC ?= gcc
CFLAGS ?= -O2 -g

SRC := $(shell echo src/*.c)
OBJ := $(SRC:.c=.o)


default: all

all: info-c

clean:
	rm -f info-c ${OBJ}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

info-c: info-c.c ${OBJ}
	${CC} ${CFLAGS} $^ -o $@

.PHONY: all clean
