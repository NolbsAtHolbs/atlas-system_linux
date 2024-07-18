CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = hnm.c hnmnm.c
OBJ = $(SRC:.c=.o)
DEPS = hnm.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

hnm: $(OBJ)
	$(CC) $(CFLAGS) -o hnm $(OBJ)

clean:
	rm -f hnm
	rm -f *.o

.PHONY: hnm clean
