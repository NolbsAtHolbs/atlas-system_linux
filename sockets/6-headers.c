#include "sockets.h"

#define HTTP200 "HTTP/1.1 200 OK\r\n\r\n"

void parse_query(char *query);

/**
 * main - opens an IPv4/TCP socket, and listens to traffic on port 8080
 * Return: 0 on success, -1 on failure
*/
int main(void)
{
	int sock_fd, client_fd;
	size_t bytes = 0;
	char buffer[4096], sent[32] = parse_query;
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
			parse_query(buffer);
		}
		send(client_fd, sent, sizeof(sent), 0);
		close(client_fd);
	}
	return (0);
}

/**
 * parse_query - parses supplied http query string
 * @query: supplied query string to parse
*/
void parse_query(char *query)
{
	int i = 0, flag = 0;
	char *token = NULL, *headers[16] = {0}, key[50], val[50];

	do {
		token = strsep(&query, "\r\n");
		if (token)
			headers[i++] = token, flag = 1;
	} while (token && flag--);

	for (i = 1; headers[i]; i++)
	{
		if (sscanf(headers[i],"%[^:]:%s", key, val) > 0)
			printf("Header: \"%s\" -> \"%s\"\n", key, val), fflush(stdout);
	}
}
