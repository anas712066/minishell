/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:07:50 by mmilitar          #+#    #+#             */
/*   Updated: 2025/06/29 20:27:25 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*get_history_path(void)
{
	const char	*home;
	const char	*filename;
	char		*full_path;

	home = getenv("HOME");
	if (!home)
		return (0);
	filename = "/.minishell_history";
	full_path = malloc(strlen(home) + ft_strlen(filename) + 1);
	if (!full_path)
		return (0);
	ft_strlcpy(full_path, home, ft_strlen(home) + ft_strlen(filename) + 1);
	ft_strlcat(full_path, filename, ft_strlen(home) + ft_strlen(filename) + 1);
	return (full_path);
}
