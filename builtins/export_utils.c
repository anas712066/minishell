/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:52:20 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 03:56:55 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_all_exported_vars(char ***env)
{
	char	**current;
	char	*equal_sign;
	char	*name;
	char	*value;
	int		name_len;

	current = *env;
	while (*current)
	{
		equal_sign = strchr(*current, '=');
		if (equal_sign)
		{
			name_len = equal_sign - *current;
			name = ft_substr(*current, 0, name_len);
			value = equal_sign + 1;
			printf("declare -x %s=\"%s\"\n", name, value);
			free(name);
		}
		else
			printf("declare -x %s\n", *current);
		current++;
	}
	return (0);
}

char	*extract_var_name(char *arg)
{
	char	*equal_sign;
	char	*var_name;
	int		name_len;

	equal_sign = strchr(arg, '=');
	if (equal_sign)
	{
		name_len = equal_sign - arg;
		var_name = ft_substr(arg, 0, name_len);
	}
	else
		var_name = ft_strdup(arg);
	return (var_name);
}

void	set_env_variable(char *arg, char *var_name)
{
	char	*equal_sign;
	char	*var_value;
	char	*existing_value;

	equal_sign = strchr(arg, '=');
	if (equal_sign)
	{
		var_value = equal_sign + 1;
		setenv(var_name, var_value, 1);
	}
	else
	{
		existing_value = getenv(var_name);
		if (existing_value)
			setenv(var_name, existing_value, 1);
	}
}

int	process_export_arg(char *arg)
{
	char	*var_name;

	var_name = extract_var_name(arg);
	if (!is_valid_identifier(var_name))
	{
		write(STDERR_FILENO, "export: ", 8);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": not a valid identifier\n", 25);
		free(var_name);
		return (1);
	}
	set_env_variable(arg, var_name);
	free(var_name);
	return (0);
}
