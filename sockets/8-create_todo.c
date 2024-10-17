#include "sockets.h"

todo_t *list = NULL;

/**
 * main - entry to the function
 * Return: 0 on success
*/
int main(void)
{
	int sock_fd, client_fd;
	size_t bytes = 0;
	char buffer[4096];
	struct sockaddr_in s_address;
	socklen_t addrlen = sizeof(s_address);

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);
	s_address.sin_family = AF_INET, s_address.sin_port = htons(8080);
	s_address.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock_fd, (struct sockaddr *)&s_address, sizeof(s_address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);
	printf("Server listening on port 8080\n");
	if (listen(sock_fd, 5) < 0)
		perror("listen failed"), exit(EXIT_FAILURE);
	while (1)
	{
		client_fd = accept(sock_fd, (struct sockaddr *)&s_address, &addrlen);
		if (client_fd < 0)
			perror("accept failed"), exit(EXIT_FAILURE);
		printf("Client connected: %s\n", inet_ntoa(s_address.sin_addr));
		bytes = recv(client_fd, buffer, 4096, 0);
		if (bytes > 0)
		{
			printf("Raw request: \"%s\"\n", buffer), fflush(stdout);
			process_req(buffer, client_fd);
		}
		close(client_fd);
	}
	return (0);
}

/**
 * process_req - processes a request
 * @request: request to process
 * @fd: file descriptor for socket connection
 */
void process_req(char *request, int fd)
{
	char meth[50], path[50];

	printf("Entering process_req\n");
	sscanf(request, "%s %s", meth, path);
	if (strcmp(meth, "POST") != 0 && strcmp(meth, "GET") != 0)
	{
		send(fd, STAT_404, sizeof(STAT_404), 0);
		return;
	}
	if (strcmp(path, "/todos") != 0)
	{
		send(fd, STAT_404, strlen(STAT_404), 0);
		return;
	}
	head_parser(request, fd);
}

/**
 * head_parser - parse an http query
 * @query: query string to parse
 * @fd: file descriptor for socket connection
 */
void head_parser(char *query, int fd)
{
	int i = 0, my_switch = 0;
	char *token = NULL, *lines[16] = {0}, *body = NULL, key[50], val[50];

	printf("Entering head_parser\n");
	do {
		token = strsep(&query, "\r\n");
		if (token)
			lines[i++] = token, my_switch = 1;
	} while (token && my_switch--);

	body = lines[i - 1];
	for (i = 1; lines[i]; i++)
	{
		sscanf(lines[i], "%[^:]:%s", key, val);
		if (strcmp(key, "Content-Length") == 0)
			my_switch = 1;
	}
	if (!my_switch)
	{
		send(fd, STAT_411, strlen(STAT_411), 0);
		return;
	}
	printf("%s\n", body);
	task_parser(body, fd);
}

/**
 * task_parser - parse an http query
 * @query: query string to parse
 * @fd: file descriptor for socket connection
*/
void task_parser(char *query, int fd)
{
	int i = 0, my_switch = 0, my_switch_k = 1, my_switch_d = 1;
	char *token = NULL, *key_vals[16] = {0}, key[50], val[50], *title, *desc;

	printf("Entering task_parser\n");
	do {
		token = strsep(&query, "&");
		if (token && token[0])
			key_vals[i++] = token, my_switch = 1;
	} while (token && my_switch--);

	for (i = 0; key_vals[i]; i++)
	{
		sscanf(key_vals[i], "%[^=]=%s", key, val);
		if (strcmp(key, "title") == 0)
			title = strdup(val), my_switch_k = 0;
		else if (strcmp(key, "description") == 0)
			desc = strdup(val), my_switch_d = 0;
	}
	if (my_switch_k && my_switch_d)
	{
		send(fd, STAT_422, strlen(STAT_422), 0);
		return;
	}
	printf("title:%s\ndesc:%s\n", title, desc);
	add_todo(desc, title, fd);
}

/**
 * add_todo - Function to add to the todo list
 * @desc: description of task
 * @title: title of task
 * @fd: file descriptor for socket connection
 */
void add_todo(char *desc, char *title, int fd)
{
	static size_t id;
	int len = 0;
	char buffer[1024];
	todo_t *new_todo = NULL, *tmp;

	printf("Entering add_todo\n");
	new_todo = calloc(1, sizeof(todo_t));
	if (!new_todo)
		return;
	new_todo->id = id;
	new_todo->title = strdup(title);
	new_todo->description = strdup(desc);
	new_todo->next = NULL;
	id++;
	if (!list)
		list = new_todo;
	else
	{
		tmp = list;
		for (; tmp; tmp = tmp->next)
		{
			if (tmp->next == NULL)
			{
				tmp->next = new_todo;
				break;
			}
		}
	}
		sprintf(buffer, "{\"id\":%lu,\"title\":\"%s\",\"description\":\"%s\"}",
				new_todo->id, title, desc);
		len = strlen(buffer);
		printf("%s\n", buffer), fflush(stdout);
		dprintf(fd, "%s", STAT_201), dprintf(fd, "Content-Length: %d\r\n", len);
		dprintf(fd, "Content-Type: application/json\r\n\r\n");
		dprintf(fd, "%s", buffer);
}
