/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:43 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 19:56:03 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	print_var_with_value(char *env_entry)
{
	char	*equal_sign;
	int		name_len;
	char	*var_name;
	char	*current_value;

	equal_sign = strchr(env_entry, '=');
	name_len = equal_sign - env_entry;
	var_name = ft_substr(env_entry, 0, name_len);
	current_value = getenv(var_name);
	if (current_value)
		printf("%s=%s\n", var_name, current_value);
	free(var_name);
}

static void	print_var_without_value(char *env_entry)
{
	char	*current_value;

	current_value = getenv(env_entry);
	if (current_value)
		printf("%s=%s\n", env_entry, current_value);
}

int	builtin_env(char **envp)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (envp[i])
	{
		equal_sign = strchr(envp[i], '=');
		if (equal_sign)
			print_var_with_value(envp[i]);
		else
			print_var_without_value(envp[i]);
		i++;
	}
	return (0);
}
