/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:50 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 20:17:11 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	builtin_export(char **args, char ***env)
{
	int	i;

	if (!args[1])
		return (print_all_exported_vars(env));
	i = 1;
	while (args[i])
	{
		if (process_export_arg(args[i], env) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	update_existing_var(char **env, char *var_name,
	char *var_value, int count)
{
	int		i;
	char	*equal_sign;
	size_t	name_len;
	char	*temp;

	i = 0;
	while (i < count)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			name_len = equal_sign - env[i];
			if (ft_strncmp(env[i], var_name, name_len) == 0
				&& name_len == ft_strlen(var_name))
			{
				free(env[i]);
				temp = ft_strjoin(var_name, "=");
				env[i] = ft_strjoin(temp, var_value);
				free(temp);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static char	**create_new_env(char **env, char *var_name,
	char *var_value, int count)
{
	char	**new_env;
	char	*temp;
	int		i;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (i < count)
	{
		new_env[i] = env[i];
		i++;
	}
	temp = ft_strjoin(var_name, "=");
	new_env[count] = ft_strjoin(temp, var_value);
	new_env[count + 1] = NULL;
	free(temp);
	return (new_env);
}

char	**add_var_to_env(char **env, char *var_name, char *var_value)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	if (update_existing_var(env, var_name, var_value, count))
		return (env);
	return (create_new_env(env, var_name, var_value, count));
}
