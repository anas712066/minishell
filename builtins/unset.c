/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:57 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 20:18:12 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../libft/libft.h"

int	builtin_unset(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unsetenv(args[i]);
		*env = remove_var_from_env(*env, args[i]);
		i++;
	}
	return (0);
}

static void	shift_env_vars(char **env, int index, int count)
{
	int	j;

	j = index;
	while (j < count - 1)
	{
		env[j] = env[j + 1];
		j++;
	}
	env[count - 1] = NULL;
}

static int	check_var_with_value(char **env, char *var_name, int i, int count)
{
	char	*equal_sign;
	size_t	name_len;

	equal_sign = ft_strchr(env[i], '=');
	name_len = equal_sign - env[i];
	if (ft_strncmp(env[i], var_name, name_len) == 0
		&& name_len == ft_strlen(var_name))
	{
		shift_env_vars(env, i, count);
		return (1);
	}
	return (0);
}

static int	check_var_without_value(char **env,
	char *var_name, int i, int count)
{
	if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
		&& ft_strlen(env[i]) == ft_strlen(var_name))
	{
		shift_env_vars(env, i, count);
		return (1);
	}
	return (0);
}

char	**remove_var_from_env(char **env, char *var_name)
{
	int		count;
	int		i;
	char	*equal_sign;

	count = 0;
	while (env[count])
		count++;
	i = 0;
	while (i < count)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			if (check_var_with_value(env, var_name, i, count))
				return (env);
		}
		else
		{
			if (check_var_without_value(env, var_name, i, count))
				return (env);
		}
		i++;
	}
	return (env);
}
