#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_unset(char **args)
{
	int	i = 1;

	while (args[i])
	{
		unsetenv(args[i]);
		i++;
	}
	return (0);
}
