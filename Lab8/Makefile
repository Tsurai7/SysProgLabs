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
all: server client
server: server.c Makefile
	$(CC) $(CFLAGS) server.c -o server
client: client.c Makefile
	$(CC) $(CFLAGS) client.c -o client
clean:
	rm -f server
	rm -f client
	rm -rf server.dSYM
	rm -rf client.dSYM