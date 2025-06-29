/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:57 by mumajeed          #+#    #+#             */
/*   Updated: 2025/06/29 03:52:01 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	builtin_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unsetenv(args[i]);
		i++;
	}
	return (0);
}
