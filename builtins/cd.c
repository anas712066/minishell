/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:40 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 03:52:41 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

char	*validate_and_get_path(char **args)
{
	int		arg_count;
	char	*path;

	arg_count = 0;
	while (args[arg_count + 1])
		arg_count++;
	if (arg_count > 1)
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (NULL);
	}
	if (arg_count == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
		return (path);
	}
	else
		return (args[1]);
}

int	builtin_cd(char **args)
{
	char	*path;

	path = validate_and_get_path(args);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
