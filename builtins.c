#include "shell.h"
#define l(x) _strlen((x))

/**
*handle_exit - decides exit code
*@cmd: list of args
*Return: exit code
*/
int handle_exit(char **cmd)
{
	int exitstatus = 0, i = 0, str_in = 0;
	char *ermsg;

	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (!('0' <= cmd[1][i] && '9' >= cmd[1][i]))
				str_in = 1;
			i++;
		}
		ermsg = smalloc(l("exit: Illegal number: ") + l(cmd[1]) + 4);
		_strcpy(ermsg, "exit: Illegal number: ");
		_strcat(ermsg, cmd[1]);

		if (str_in)
		{
			errno = -1;
			perr(NULL, NULL, ermsg);
			exitstatus = 2;

		}
		else if (_atoi(cmd[1]) < 0)
		{
			errno = -1;
			perr(NULL, NULL, ermsg);
			exitstatus = 2;
		}
		else
			exitstatus = _atoi(cmd[1]) % 256;

		free(ermsg);
	}
	return (exitstatus);
}
/**
 *handlebin - handles builtin commands
 *@cmd: command arguements
 *@head: head of the alias list
 *Return: 0 if builting commond executed or 1 if not
 */
int *handlebin(char **cmd, alias **head)
{
	int *ret = smalloc(2 * sizeof(int));

	ret[0] = 1, ret[1] = 266;
	if (!cmd)
		return (ret);
	if (!_strcmp(cmd[0], "exit"))
		ret[0] = 0, ret[1] = handle_exit(cmd);
	else if (!_strcmp(cmd[0], "env") || !_strcmp(cmd[0], "printenv"))
		_printenv(), ret[0] = 0;
	else if (!_strcmp(cmd[0], "\n"))
		ret[0] = 0;
	else if (!_strcmp(cmd[0], "setenv"))
	{
		if (arlen(cmd) != 3)
			errno = -2, perr(NULL, NULL, "Too few or too many arguements");
		else
			_setenv(cmd[1], cmd[2], 0);
		ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "unsetenv"))
	{
		if (arlen(cmd) != 2)
			errno = -2, perr(NULL, NULL, "Too few or too many arguements");
		else
			_unsetenv(cmd[1]);
		ret[0] = 0;
	}
	else if (!_strcmp(cmd[0], "cd"))
		_chdir(arlen(cmd) > 1 ? cmd[1] : NULL),	ret[0] = 0;
	else if (!_strcmp(cmd[0], "history"))
		phistory(), ret[0] = 0;
	else if (!_strcmp(cmd[0], "help"))
		phelp(arlen(cmd) > 1 ? cmd[1] : NULL),	ret[0] = 0;
	else if (!_strcmp(cmd[0], "alias"))
		handle_alias(cmd, head), ret[0] = 0;

	if (!ret[0] && ret[1] == 266)
		freedp(cmd);
	return (ret);
}
