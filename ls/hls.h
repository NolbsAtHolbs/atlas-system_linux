#ifndef HlS_H
#define HlS_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

void handle_errors(char *program_name, char *path);
char *my_strdup(const char *s, char *program_name);
void *xmalloc(size_t size, char *program_name);
void *xrealloc(void *ptr, size_t size, char *program_name);
void sort_entries(char **entries, int count);
int compare_strings(const char *a, const char *b);

#endif
