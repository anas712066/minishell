/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:50 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 03:51:51 by mmilitar         ###   ########.fr       */
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
		if (process_export_arg(args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
