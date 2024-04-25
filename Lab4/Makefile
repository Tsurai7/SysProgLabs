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
all: main consumer producer
main: main.c Makefile
	$(CC) $(CFLAGS) main.c -o main
producer: producer.c Makefile
	$(CC) $(CFLAGS) producer.c -o producer
consumer: consumer.c Makefile
	$(CC) $(CFLAGS) consumer.c -o consumer
clean:
	rm -f main
	rm -f producer
	rm -f consumer
	rm -rf main.dSYM
	rm -rf producer.dSYM
	rm -rf consumer.dSYM