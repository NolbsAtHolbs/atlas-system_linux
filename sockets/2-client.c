#include "sockets.h"

/**
 * main - connects to a listening server
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, -1 on failure
 */
int main(int argc, char *argv[])
{
	int sock_fd;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	unsigned short port;

	if (argc != 3) /* validate command-line args */
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = (unsigned short)atoi(argv[2]); /* convert port to unsigned short */

	sock_fd = socket(AF_INET, SOCK_STREAM, 0); /* create socket */
	if (sock_fd == -1)
		perror("socket failed"), exit(EXIT_FAILURE);

	server = gethostbyname(argv[1]); /* get server by hostname */
	if (server == NULL)
		fprintf(stderr, "No such host: %s\n", argv[1]), exit(EXIT_FAILURE);

	/* initialize server address structure */
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

	/* connect to the server */
	if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		perror("connect failed"), exit(EXIT_FAILURE);

	printf("Connected to %s:%d\n", argv[1], port);
	close(sock_fd);
	return (EXIT_SUCCESS);
}
