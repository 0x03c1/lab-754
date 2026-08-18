CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c11 -O2

PROGRAMAS = dissect patriot monstros

.PHONY: all

all: $(PROGRAMAS)

dissect: src/dissect.c
	$(CC) $(CFLAGS) src/dissect.c -o dissect

patriot: src/patriot.c
	$(CC) $(CFLAGS) src/patriot.c -o patriot

monstros: src/monstros.c
	$(CC) $(CFLAGS) src/monstros.c -o monstros
