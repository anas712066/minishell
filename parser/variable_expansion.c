#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"
#include "../libft/libft.h"

static void	copy_exit_code(char *result, int *j)
{
	char	*exit_code_str;
	int		k;

	exit_code_str = ft_itoa(g_last_status);
	if (exit_code_str)
	{
		k = 0;
		while (exit_code_str[k])
			result[(*j)++] = exit_code_str[k++];
		free(exit_code_str);
	}
}

static void	copy_var_value(char *result, int *j, char *var_value)
{
	int	k;

	if (var_value)
	{
		k = 0;
		while (var_value[k])
			result[(*j)++] = var_value[k++];
	}
}

static int	expand_normal_variable(char *str, int i, char *result, int *j)
{
	int		start;
	int		end;
	char	*var_name;
	char	*var_value;

	start = i + 1;
	end = start;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	if (end > start)
	{
		var_name = ft_substr(str, start, end - start);
		if (var_name)
		{
			var_value = getenv(var_name);
			copy_var_value(result, j, var_value);
			free(var_name);
		}
		return (end);
	}
	else
	{
		result[(*j)++] = str[i];
		return (i + 1);
	}
}

char	*expand_variables(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(2048);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				copy_exit_code(result, &j);
				i += 2;
			}
			else
				i = expand_normal_variable(str, i, result, &j);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}