CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
TARGET = 0-hreadelf
SRCS = 0-are.c 0-fhinfo.c 0-swaps.c
OBJS = $(SRCS:.c=.o)
HDRS = hreadelf.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
