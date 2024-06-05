CC = gcc
CFLAGS_DEBUG = -g -ggdb -std=c11 -pedantic -W -Wall -Wextra
CFLAGS_RELEASE = -std=c11 -pedantic -W -Wall -Wextra -Werror
.PHONY: clean all
MODE ?= debug
ifeq ($(MODE), debug)
	CFLAGS = $(CFLAGS_DEBUG)
else
	CFLAGS = $(CFLAGS_RELEASE)
endif
all: sort_index
main: sort_index.c Makefile
	$(CC) $(CFLAGS) sort_index.c -o sort_index
clean:
	rm -f sort_index
	rm -rf sort_index.dSYM