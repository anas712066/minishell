#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>

// Función para obtener el path de historial en $HOME
char	*get_history_path(void)
{
	const char	*home = getenv("HOME");
    if (!home)
        return NULL;
    
    const char *filename = "/.minishell_history";
    char *full_path = malloc(strlen(home) + strlen(filename) + 1);
    if (!full_path)
        return NULL;
    
    strcpy(full_path, home);
    strcat(full_path, filename);
    return full_path;
}

int	main(void)
{
	char	*input;
	char	*hist_path = get_history_path();

    // Cargar hist
	{
		read_history(hist_path);
	}
        

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
	// Guardar historial antes de salir
	if (hist_path)
    {
        write_history(hist_path);
        free(hist_path);
    }

	return (0);
}
