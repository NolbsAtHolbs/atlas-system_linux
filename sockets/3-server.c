#include "sockets.h"

/**
 * main - opens an IPv4/TCP socket, listens to traffic on port 12345 @ any addr
 * Return: 0 on success, -1 on failure
 */
int main(void)
{
	int sock_fd, client_fd;
	struct sockaddr_in address, client_addr;
	socklen_t client_len = sizeof(client_addr);
	char *client_ip;
	char buffer[1024];
	ssize_t bytes_received;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0); /* create socket */
	if (sock_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);

	memset(&address, 0, sizeof(address)); /* initialize address structure */
	address.sin_family = AF_INET;
	address.sin_port = htons(12345);
	address.sin_addr.s_addr = INADDR_ANY;

	/* bind the socket to the address and port */
	if (bind(sock_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);

	printf("Server listening on port 12345\n");

	if (listen(sock_fd, 5) < 0) /* start listening */
		perror("listen failed"), exit(EXIT_FAILURE);

	/* accept an incoming connection */
	client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd < 0)
		perror("accept failed"), exit(EXIT_FAILURE);

	client_ip = inet_ntoa(client_addr.sin_addr); /* get client's IP address */
	printf("Client connected: %s\n", client_ip);

	memset(buffer, 0, sizeof(buffer)); /* receive message from client */
	bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_received < 0)
		perror("recv failed"), exit(EXIT_FAILURE);

	printf("Message received: \"%s\"\n", buffer);
	close(client_fd);
	close(sock_fd);
	return (EXIT_SUCCESS);
}
