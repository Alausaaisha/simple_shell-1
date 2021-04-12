#ifndef SHELL_H
#define SHELL_H
extern char **environ;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
void print_environ();
int _strcmp(char *s1, char *s2);
#endif
