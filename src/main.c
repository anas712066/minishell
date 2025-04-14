#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		// Aquí procesarías la línea, por ahora solo la imprimimos
		printf("Recibido: %s\n", input);
		free(input);
	}
	return (0);
}
