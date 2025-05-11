/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:58:57 by mumajeed          #+#    #+#             */
/*   Updated: 2025/05/11 12:58:58 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_unset(char **args)
{
	int	i = 1;

	while (args[i])
	{
		unsetenv(args[i]);
		i++;
	}
	return (0);
}
