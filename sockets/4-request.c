#include "sockets.h"

/**
 * main - opens an IPv4/TCP socket, listens to traffic on port 8080 @ any addr
 * Return: 0 upon success
 */
int main(void)
{
	int serv_fd, client_fd;
	struct sockaddr_in serv_addr, client_addr;
	socklen_t cli_len = sizeof(client_addr);
	ssize_t bytes_read;
	char *client_ip, method[8], path[1024], version[16], buffer[BUFSIZ];

	serv_fd = socket(AF_INET, SOCK_STREAM, 0); /* create socket */
	if (serv_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);
	int opt = 1; /* set socket options */
	if (setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		perror("setsockopt failed"), exit(EXIT_FAILURE);
	memset(&serv_addr, 0, sizeof(serv_addr)); /* init serv adr structure */
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);
	printf("Server listening on port 8080\n");
	if (listen(serv_fd, 5) < 0) /* start listening */
		perror("listen failed"), exit(EXIT_FAILURE);
	while (1)
	{ /* accept an incoming connection */
		client_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &cli_len);
		if (client_fd < 0)
			perror("accept failed"), exit(EXIT_FAILURE);
		client_ip = inet_ntoa(client_addr.sin_addr); /* get client's IP addr */
		printf("Client connected: %s\n", client_ip);
		memset(buffer, 0, sizeof(buffer)); /* receive HTTP request */
		bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes_read < 0)
			perror("recv failed"), exit(EXIT_FAILURE);
		printf("Raw request: \"%s\"\n", buffer); /* print raw HTTP request */
		sscanf(buffer, "%7s %1023s %15s", method, path, version); /* parse */
		printf("Method: %s\n", method);
		printf("Path: %s\n", path);
		printf("Version: %s\n", version);
		const char *response = "HTTP/1.1 200 OK\r\n\r\n"; /* send HTTP200 OK */
		if (send(client_fd, response, strlen(response), 0) < 0)
			perror("send failed"), exit(EXIT_FAILURE);
		close(client_fd);
	}
	close(serv_fd);
	return (EXIT_SUCCESS);
}
