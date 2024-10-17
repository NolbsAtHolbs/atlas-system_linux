#include "sockets.h"

#define MESSAGE "HTTP/1.1 200 OK\r\n\r\n"

void parse_query(char *query);

/**
 * main - Socket API
 * Return: Success or Failure
*/
int main(void)
{
	int socket_fd, client_fd;
	ssize_t bytes;
	char buffer[4096], method[16], full_path[256], path[256], query[256];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addrlen = sizeof(client_addr);

	/* create socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	/* set socket options */
	int opt = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt failed");
		close(socket_fd);
		exit(EXIT_FAILURE);
	}

	/* initialize server address structure */
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	/* bind the socket */
	if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind failed");
		close(socket_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port 8080\n");

	/* start listening */
	if (listen(socket_fd, 5) < 0)
	{
		perror("listen failed");
		close(socket_fd);
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		/* accept an incoming connection */
		client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addrlen);
		if (client_fd < 0)
		{
			perror("accept failed");
			continue;
		}

		printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

		/* receive data */
		bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes > 0)
		{
			buffer[bytes] = '\0'; /* null-terminate the buffer */
			printf("Raw request: \"%s\"\n", buffer);

			/* parse the request line */
			if (sscanf(buffer, "%15s %255s", method, full_path) == 2)
			{
				/* split the path and query */
				char *question_mark = strchr(full_path, '?');
				if (question_mark)
				{
					*question_mark = '\0';
					strncpy(path, full_path, sizeof(path) - 1);
					path[sizeof(path) - 1] = '\0';
					strncpy(query, question_mark + 1, sizeof(query) - 1);
					query[sizeof(query) - 1] = '\0';
				}
				else
				{
					strncpy(path, full_path, sizeof(path) - 1);
					path[sizeof(path) - 1] = '\0';
					query[0] = '\0';
				}

				printf("Path: %s\n", path);

				if (query[0] != '\0')
					parse_query(query);
			}
			else
			{
				printf("Failed to parse request line\n");
			}
		}
		else if (bytes == 0)
		{
			printf("Client disconnected\n");
		}
		else
		{
			perror("recv failed");
		}

		/* send response */
		if (send(client_fd, MESSAGE, strlen(MESSAGE), 0) < 0)
		{
			perror("send failed");
		}

		/* close client socket */
		close(client_fd);
	}

	/* close server socket */
	close(socket_fd);

	return 0;
}

/**
 * parse_query - parses supplied HTTP query string
 * @query: supplied query string to parse
 */
void parse_query(char *query)
{
	char *key_value, *key, *value;
	char *rest = query;

	while ((key_value = strtok_r(rest, "&", &rest)))
	{
		key = key_value;
		value = strchr(key_value, '=');
		if (value)
		{
			*value = '\0';
			value++;
		}
		else
		{
			value = "";
		}
		printf("Query: \"%s\" -> \"%s\"\n", key, value);
	}
}
