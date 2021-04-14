#include "shell.h"

/**
  * main - entry point of the program
  * Return: 0
  */
int main(void)
{
	char *buffer = NULL, **cmd = NULL;
	int status;
	size_t bufsize = 0;
	pid_t child_pid;

	signal(SIGINT, SIG_IGN);
	while (1)
	{
		printf("~$ ");
		if (getline(&buffer, &bufsize, stdin) == -1)
			break;
		if (buffer == NULL)
		{
			perror("memory allocation failed");
			exit(0);
		}
		cmd = parse_input_string(buffer);
		if (!cmd[0])
		{
			free(cmd);
			continue;
		}
		if (_strcmp(cmd[0], "env") == 0)
		{
			print_environ();
			continue;
		}
		if (_strcmp(cmd[0], "exit") == 0)
		{
			free(cmd);
			free(buffer);
			return (0);
		}
		child_pid = fork();
		if (child_pid < 0)
			perror("could not create child process");
		else if (child_pid == 0)
		{
			if (_strchr(cmd[0], '/') == NULL)
				cmd[0] = path_search(cmd[0]);
			if (execve(cmd[0], cmd, NULL))
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (child_pid > 0)
			wait(&status);
		free(cmd);
	}
	free(buffer);
	return (0);
}
