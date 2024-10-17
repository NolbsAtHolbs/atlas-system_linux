#include "sockets.h"

#define HTTP200 "HTTP/1.1 200 OK\r\n\r\n"

/**
 * main - opens an IPv4/TCP socket, listens to traffic on port 8080 @ any addr
 * Return: 0 upon success
 */
int main(void)
{
	int socket_fd, connect;
	size_t bytes = 0;
	char buffer[4096], meth[50], path[50], ver[50], sent[32] = HTTP200;
	struct sockaddr_in s_address;
	socklen_t addrlen = sizeof(s_address);

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);
	s_address.sin_family = AF_INET, s_address.sin_port = htons(8080);
	s_address.sin_addr.s_addr = INADDR_ANY;
	if (bind(socket_fd, (struct sockaddr *)&s_address, sizeof(s_address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);
	printf("Server listening on port 8080\n");
	if (listen(socket_fd, 5) < 0)
		perror("listen failed"), exit(EXIT_FAILURE);
	while (1)
	{
		connect = accept(socket_fd, (struct sockaddr *)&s_address, &addrlen);
		if (connect < 0)
			perror("accept failed"), exit(EXIT_FAILURE);
		printf("Client connected: %s\n", inet_ntoa(s_address.sin_addr));
		bytes = recv(connect, buffer, 4096, 0);
		if (bytes > 0)
		{
			printf("Raw request: \"%s\"\n", buffer), fflush(stdout);
			sscanf(buffer, "%s %s %s", meth, path, ver);
			printf("Method: %s\nPath: %s\nVersion: %s\n", meth, path, ver);
			fflush(stdout);
		}
		send(connect, sent, sizeof(sent), 0);
		close(connect);
	}
	return (0);
}
