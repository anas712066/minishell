#include "../include/builtins.h"
#include <stdio.h>

int builtin_echo(char **args)
{
	int i = 1;
	int newline = 1;

	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}