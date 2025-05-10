#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_exit(char **args)
{
	printf("exit\n");
	if (args[1])
		exit(atoi(args[1]));
	else
		exit(0);
}
