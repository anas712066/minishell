#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_env(char **envp)
{
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	return (0);
}
