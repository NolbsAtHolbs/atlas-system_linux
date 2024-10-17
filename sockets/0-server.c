#include "sockets.h"

/*
* main - opens an IPv4/TCP socket, listens to traffic on port 12345 @ any addr
* Return: 0 on success, -1 on failure
*/
int main(void)
{
	int socket_file_descriptor;
	struct sockaddr_in sai;

	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0); /* create sock */
	if (socket_file_descriptor == -1)
		perror("socket failed"), exit(EXIT_FAILURE);

	sai.sin_family = AF_INET; /* initialize address structure */
	sai.sin_port = htons(12345);
	sai.sin_addr.s_addr = INADDR_ANY;

	/* bind the socket to the address and port */
	if (bind(socket_file_descriptor, (struct sockaddr *)&sai, sizeof(sai)) < 0)
		perror("bind failed"), exit(EXIT_FAILURE);

	printf("Listening on Port 12345\n");

	if (listen(socket_file_descriptor, 5) < 0) /* start listening */
		perror("listen failed"), exit(EXIT_FAILURE);

	while (1) /* hang indefinitely */
		;

	return (EXIT_SUCCESS);
}
