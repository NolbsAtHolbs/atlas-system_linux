CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g

SRC_0 = $(wildcard 0-*.c)
SRC_1 = $(wildcard 1-*.c)
SRC_2 = $(wildcard 2-*.c)
SRC_3 = $(wildcard 3-*.c)

OBJ_0 = $(SRC_0:.c=.o)
OBJ_1 = $(SRC_1:.c=.o)
OBJ_2 = $(SRC_2:.c=.o)
OBJ_3 = $(SRC_3:.c=.o)

.PHONY: all strace_0 strace_1 strace_2 strace_3 clean

# Compile all programs
all: strace_0 strace_1 strace_2 strace_3

# Syscall number
strace_0: $(OBJ_0)
	$(CC) $(CFLAGS) $^ -o $@

# Syscall name
strace_1: $(OBJ_1)
	$(CC) $(CFLAGS) $^ -o $@

# Syscall return value
strace_2: $(OBJ_2)
	$(CC) $(CFLAGS) $^ -o $@

# Syscall raw parameters and return value
strace_3: $(OBJ_3)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and binaries
clean:
	rm -f strace_0 strace_1 strace_2 strace_3
	rm -f *.o
