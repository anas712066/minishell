#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_export(char **args, char ***envp)
{
	int	i = 1;
	if (!args[1])
		return (builtin_env(*envp));
	while (args[i])
	{
		putenv(args[i]); // ⚠️ Usa setenv/putenv solo si el formato es correcto
		i++;
	}
	return (0);
}
