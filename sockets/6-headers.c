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
	size_t received_bytes = 0;
	char request_buffer[4096], response[] = HTTP200;
	struct sockaddr_in server_address;
	socklen_t address_length = sizeof(server_address);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8080);
	server_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);
	printf("Server listening on port 8080\n");
	if (listen(server_fd, 5) < 0)
		perror("listen failed"), exit(EXIT_FAILURE);
	while (1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&server_address, &address_length);
		if (client_fd < 0)
			perror("accept failed"), exit(EXIT_FAILURE);
		printf("Client connected: %s\n", inet_ntoa(server_address.sin_addr));
		received_bytes = recv(client_fd, request_buffer, sizeof(request_buffer) - 1, 0);
		if (received_bytes > 0)
		{
			request_buffer[received_bytes] = '\0';
			printf("Raw request: \"%s\"\n", request_buffer), fflush(stdout);
			parse_headers(request_buffer);
		}
		send(client_fd, response, strlen(response), 0);
		close(client_fd);
	}
	return (EXIT_SUCCESS);
}

void parse_headers(char *request)
{
	char *header_line, *header_array[16] = {0}, header_key[50], header_val[50];
	int i, header_count = 0;

	while ((header_line = strsep(&request, "\r\n")) != NULL)
	{
		if (header_count < 16)
			header_array[header_count++] = header_line;
	}
	for (i = 1; i < header_count; i++)
	{
		if (sscanf(header_array[i], "%[^:]: %[^\r\n]", header_key, header_val) == 2)
			printf("Header: \"%s\" -> \"%s\"\n", header_key, header_val), fflush(stdout);
	}
}
