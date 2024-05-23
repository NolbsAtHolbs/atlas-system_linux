#ifndef HLS_H
#define HLS_H

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
int is_option(char *arg, const char *option);
void list_directory(char *path, char *program_name, int single_column);
char **read_entries(DIR *dir, int *count, char *program_name);
void process_arguments(int argc, char *argv[], int *single_column, int *start);
int count_files_and_folders(int argc, char *argv[], int start);
void sort_paths(int argc, char *argv[], int start);
int compare_paths(char *a, char *b);

#endif
