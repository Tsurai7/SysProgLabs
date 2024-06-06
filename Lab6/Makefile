CC=gcc
CFLAGS=-Wall -Wextra -pthread -O2 -D_POSIX_C_SOURCE=200112L

SRCS_FILEGENERATOR=file_generator.c
SRCS_FILESORTER=file_sorter.c

OBJS_FILEGENERATOR=$(SRCS_FILEGENERATOR:.c=.o)
OBJS_FILESORTER=$(SRCS_FILESORTER:.c=.o)

all: file_generator file_sorter

file_generator: $(OBJS_FILEGENERATOR)
	$(CC) $(CFLAGS) $(OBJS_FILEGENERATOR) -o $@

file_sorter: $(OBJS_FILESORTER)
	$(CC) $(CFLAGS) $(OBJS_FILESORTER) -o $@

clean:
	rm -f $(OBJS_FILEGENERATOR) $(OBJS_FILESORTER) file_generator file_sorter