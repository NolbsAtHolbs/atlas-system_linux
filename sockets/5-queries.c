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
	char buffer[4096], meth[50], path[50], query[255], sent[32] = HTTP200;
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
			sscanf(buffer, "%s %[^?]?%s", meth, path, query);
			printf("Path: %s\n", path), fflush(stdout);
			parse_query(query);
		}
		send(client_fd, sent, sizeof(sent), 0);
		close(client_fd);
	}
	return (EXIT_SUCCESS);
}

/**
 * parse_query - parses supplied http query
 * @query: suppplied query string to parse
*/
void parse_query(char *query)
{
	int i = 0, flag = 0;
	char *token = NULL, *key_vals[16] = {0}, key[50], val[50];

	do {
		token = strsep(&query, "&");
		if (token && token[0])
			key_vals[i++] = token, flag = 1;
	} while (token && flag--);

	for (i = 0; key_vals[i]; i++)
	{
		sscanf(key_vals[i],"%[^=]=%s", key, val);
		printf("Query: \"%s\" -> \"%s\"\n", key, val), fflush(stdout);
	}
}
