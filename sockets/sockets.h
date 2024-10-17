#ifndef SOCKETS_H
#define SOCKETS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define STAT_201 "HTTP/1.1 201 Created\r\n"
#define STAT_404 "HTTP/1.1 404 Not Found\r\n\r\n"
#define STAT_411 "HTTP/1.1 411 Length Required\r\n\r\n"
#define STAT_422 "HTTP/1.1 422 Unprocessable Entity\r\n\r\n"

typedef struct todo
{
    size_t id;
    char *title;
    char *description;
    struct todo *next;
} todo_t;

void process_req(char *request, int fd);
void head_parser(char *query, int fd);
void task_parser(char *query, int fd);
void add_todo(char *desc, char *title, int fd);

#endif