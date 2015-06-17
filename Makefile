CC=gcc
CFLAGS=-O0

all:
	make sequential_access
	make random_access

clean:
	rm sequential_access
	rm random_access
