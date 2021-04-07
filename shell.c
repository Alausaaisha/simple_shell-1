#include "shell.h"

/**
  * main - entry point of the program
  * @ac: argument counter.
  * @av: argument vector.
  * @envp: NULL terminated array of strings.
  * Return: 0
  */
int main(int ac __attribute__((unused)), char **av __attribute__
		((unused)), char **envp)
{
	char *buffer, *token;
	int characters, status;
	size_t bufsize = 1024;
	pid_t child_pid;

	buffer = (char *)malloc(bufsize);
	if (buffer == NULL)
		return (0);
	while (1)
	{
		/* prompt for the user to enter command */
		printf("~$ ");
		/* reading line typed by user from stdin */
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
			break;
		/* split what user enters to obtain the first word/command */
		token = strtok(buffer, "\n");
		/* create a new process */
		child_pid = fork();
		/* cmd will hold the first word/command from stdin */
		char *cmd[] = {token, NULL};

		if (child_pid == 0)
		{
			/* creating a separate process using execve sys call */
			if (execve(cmd[0], cmd, envp))
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		if (child_pid > 0)
			wait(&status);
	}
	putchar('\n');
	free(buffer);
	return (0);
}
