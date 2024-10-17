CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic

all: todo_api_0 todo_api_1 todo_api_2 todo_api_3 todo_api_4 todo_api_5

todo_api_0: $(4)
	$(CC) $(CFLAGS) 4-request.c -o todo_api_0

todo_api_1: $(5)
	$(CC) $(CFLAGS) 5-queries.c -o todo_api_1

todo_api_2: $(6)
	$(CC) $(CFLAGS) 6-headers.c -o todo_api_2

todo_api_3: $(7)
	$(CC) $(CFLAGS) 7-body_parameters.c -o todo_api_3

todo_api_4: $(8)
	$(CC) $(CFLAGS) 8-create_todo.c -o todo_api_4

todo_api_5: $(9)
	$(CC) $(CFLAGS) 9-retrieve_todos.c -o todo_api_5

clean:
	rm -f todo_api_*

.PHONY: all clean
