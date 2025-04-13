/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:26:54 by mmilitar          #+#    #+#             */
/*   Updated: 2024/09/10 13:27:19 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	const char	*last;

	ch = (char)c;
	last = NULL;
	while (*s != '\0')
	{
		if (*s == ch)
			last = s;
		s++;
	}
	if (*s == ch)
		last = s;
	return ((char *)last);
}
