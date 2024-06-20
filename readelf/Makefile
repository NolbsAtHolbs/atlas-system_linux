CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
TARGETS = 0-hreadelf 1-hreadelf
SRCS_0 = 0-are.c swapfunctions.c 0-fhinfo.c
SRCS_1 = 1-are.c swapfunctions.c 1-shinfo.c
OBJS_0 = $(SRCS_0:.c=.o)
OBJS_1 = $(SRCS_1:.c=.o)
HDRS = hreadelf.h
all: $(TARGETS)
0-hreadelf: $(OBJS_0)
	$(CC) $(CFLAGS) -o $@ $(OBJS_0)

1-hreadelf: $(OBJS_1)
	$(CC) $(CFLAGS) -o $@ $(OBJS_1)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_0) $(OBJS_1) $(TARGETS)

rebuild: clean all

.PHONY: all clean rebuild
