/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilitar <mmilitar@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:10:47 by mmilitar          #+#    #+#             */
/*   Updated: 2024/10/19 19:10:53 by mmilitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	*ft_word_dup(char const *s, size_t len)
{
	char	*word;

	word = ft_substr(s, 0, len);
	return (word);
}

static void	ft_free_split(char **split, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	**ft_split_words(char const *s, char c, char **split)
{
	size_t	i;
	size_t	j;
	size_t	word_start;

	i = 0;
	j = 0;
	word_start = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i -1] == c))
			word_start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			split[j] = ft_word_dup(s + word_start, i - word_start + 1);
			if (!split[j])
			{
				ft_free_split(split, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	split = (char **)ft_calloc((word_count + 1), sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_split_words(s, c, split));
}
