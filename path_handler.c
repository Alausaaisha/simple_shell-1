#include "shell.h"

/**
  * *path_search - makes a complete path from path.
  * @cmd: command to make complete path from.
  * Return: complete path.
  */
char *path_search(char *cmd)
{
	char *path = NULL, *token = NULL, ch = '/';
	char *dirs[1024];
	int i;

	path = getenv("PATH");
	token = strtok(path, ":");
	if (dirs == NULL)
	{
		perror("memory could not be allocated");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (token != NULL)
	{
		dirs[i] = token;
		token = strtok(NULL, ":");
		i++;
	}
	dirs[i] = NULL;
	char *cwd = getcwd(NULL, 0);
	struct stat sb;

	i = 0;
	while (dirs[i] != NULL)
	{
		chdir(dirs[i]);
		if (stat(cmd, &sb) == 0)
		{
			dirs[i] = _strncat(dirs[i], &ch, 1);
			cmd = _strcat(dirs[i], cmd);
			break;
		}
		i++;
	}
	chdir(cwd);
	return (cmd);
}