#include "sockets.h"

#define PORT 8080
#define RESPONSE "HTTP/1.1 200 OK\r\n\r\n"

void parse_http_parameters(char *request);
char *make_response(char *address, char *request);

int main(void)
{
	int socket_fd, client_fd;
	size_t bytes = 0;
	char buffer[4096], client_addr[INET_ADDRSTRLEN];
	struct sockaddr_in serv_addr;
	socklen_t addrlen = sizeof(serv_addr);

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", PORT);
	if (listen(socket_fd, 5) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		client_fd = accept(socket_fd, (struct sockaddr *)&serv_addr, &addrlen);
		if (client_fd < 0)
		{
			perror("accept failed");
			exit(EXIT_FAILURE);
		}
		inet_ntop(AF_INET, &serv_addr.sin_addr, client_addr, sizeof(client_addr));
		bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			make_response(client_addr, buffer);
		}
		send(client_fd, RESPONSE, strlen(RESPONSE), 0);
		close(client_fd);
	}
	close(socket_fd);
	return (EXIT_SUCCESS);
}

char *make_response(char *address, char *request)
{
	printf("Client connected: %s\n", address);
	printf("Raw request: \"%s\"\n", request);
	parse_http_parameters(request);
	fflush(stdout);
	return strdup(RESPONSE);
}

void parse_http_parameters(char *request)
{
	char *body_params = strstr(request, "\r\n\r\n") + 4;
	char *path = strtok(strtok(strchr(request, ' ') + 1, " "), "?");
	char *key, *value;
	printf("Path: %s\n", path);
	for (
		key = strtok(body_params, "="), value = strtok(NULL, "&");
		key && value;
		key = strtok(NULL, "="), value = strtok(NULL, "&")
	)
	{
		printf("Body param: \"%s\" -> \"%s\"\n", key, value);
	}
}
