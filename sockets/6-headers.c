#include "sockets.h"

#define HTTP200 "HTTP/1.1 200 OK\r\n\r\n"

void parse_headers(char *query);

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 8080
 * Return: 0 on success, -1 on failure
*/
int main(void)
{
	int server_fd, client_fd;
	ssize_t bytes_read;
	char buffer[4096];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addrlen = sizeof(client_addr);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port 8080\n");
	if (listen(server_fd, 5) < 0)
	{
		perror("listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
		if (client_fd < 0)
		{
			perror("accept failed");
			continue;
		}
		printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
		bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0'; /* null-terminate the buffer */
			printf("Raw request: \"%s\"\n", buffer);
			parse_headers(buffer);
		}
		else if (bytes_read == 0)
		{
			printf("Client disconnected\n");
		}
		else
		{
			perror("recv failed");
		}
		if (send(client_fd, HTTP200, strlen(HTTP200), 0) < 0)
		{
			perror("send failed");
		}
		close(client_fd);
	}
	close(server_fd);
	return (EXIT_SUCCESS);
}

/**
 * parse_headers - Parses and prints HTTP headers from the buffer
 * @buffer: The buffer containing the HTTP request
 */
void parse_headers(char *buffer)
{
	char *line, *headers, *key, *value;

	headers = strstr(buffer, "\r\n");
	if (!headers)
		return;

	headers += 2; /* move past the first CRLF */

	/* iterate over each header line */
	line = strtok(headers, "\r\n");
	while (line && line[0] != '\0')
	{
		key = line;
		value = strchr(line, ':');
		if (value)
		{
			*value = '\0'; /* null-terminate the key */
			value++;       /* move past ':' */

			/* skip leading whitespace in value */
			while (*value == ' ' || *value == '\t')
				value++;

			printf("Header: \"%s\" -> \"%s\"\n", key, value);
		}
		line = strtok(NULL, "\r\n");
	}
}
