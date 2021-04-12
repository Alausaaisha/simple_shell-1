#include "shell.h"

/**
  * main - entry point of the program
  * @ac: argument counter.
  * @av: argument vector.
  * Return: 0
  */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	char *buffer, *token, *cmd[100];
	int characters, status, i;
	size_t bufsize = 1024;
	pid_t child_pid;

	buffer = (char *)malloc(bufsize);
	if (buffer == NULL)
		return (0);
	while (1)
	{
		printf("~$ ");
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
			break;
		token = strtok(buffer, " \n");
		if (strcmp(token, "exit") == 0)
			return (0);
		if (strcmp(token, "env") == 0)
		{
			print_environ();
		}
		else
		{
			for (i = 0; i < 20 && token != NULL; i++)
			{
				cmd[i] = token;
				if (strcmp(cmd[i], "exit") == 0)
					return (0);

				token = strtok(NULL, " \n");
			}
			cmd[i] = NULL;
			child_pid = fork();
			if (child_pid == 0)
			{
				if (execve(cmd[0], cmd, NULL))
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
		}
		if (child_pid > 0)
			wait(&status);
	}
	putchar('\n');
	free(buffer);
	return (0);
}
