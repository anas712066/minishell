#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_cd(char **args)
{
	const char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			perror("cd");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
