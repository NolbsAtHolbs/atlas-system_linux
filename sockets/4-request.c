#include "sockets.h"

#define HTTP200 "HTTP/1.1 200 OK\r\n\r\n"

/**
 * main - opens an IPv4/TCP socket, listens to traffic on port 8080 @ any addr
 * Return: 0 upon success
 */
int main(void)
{
	int sock_fd, client_fd;
	size_t bytes = 0;
	char buffer[4096], meth[50], path[50], ver[50];
	const char *response = HTTP200;
	struct sockaddr_in serv_addr, client_addr;
	socklen_t addrlen = sizeof(client_addr);

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("bind failed");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port 8080\n");

	if (listen(sock_fd, 5) < 0)
	{
		perror("listen failed");
		close(sock_fd);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &addrlen);
		if (client_fd < 0)
		{
			perror("accept failed");
			close(sock_fd);
			exit(EXIT_FAILURE);
		}
		printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
		memset(buffer, 0, sizeof(buffer));
		bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			printf("Raw request: \"%s\"\n", buffer);
			sscanf(buffer, "%49s %49s %49s", meth, path, ver);
			printf("Method: %s\n", meth);
			printf("Path: %s\n", path);
			printf("Version: %s\n", ver);
		}
		else if (bytes == 0)
			printf("Client disconnected unexpectedly\n");
		else
		{
			perror("recv failed");
			close(client_fd);
			continue;
		}
		if (send(client_fd, response, strlen(response), 0) < 0)
			perror("send failed");
		close(client_fd);
	}
	close(sock_fd);
	return (EXIT_SUCCESS);
}
