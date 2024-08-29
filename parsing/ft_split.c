/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:46:33 by lle-pier          #+#    #+#             */
/*   Updated: 2024/08/28 16:43:31 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			nb_word++;
		i++;
	}
	return (nb_word);
}

static int	create_array(char **array, char const *s, char c, int line)
{
	int	start_w;
	int	end_w;

	start_w = 0;
	end_w = 0;
	while (s[end_w])
	{
		if (s[end_w] == c || s[end_w] == 0)
			start_w = end_w + 1;
		if (s[end_w] != c && (s[end_w + 1] == c || s[end_w + 1] == 0))
		{
			array[line] = malloc(sizeof(char) * (end_w - start_w + 2));
			if (!array[line])
			{
				while (line > 0)
					free(array[--line]);
				free (array);
				return (0);
			}
			ft_strlcpy(array[line++], (s + start_w), (end_w - start_w + 2));
		}
		end_w++;
	}
	array[line] = 0;
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!array)
		return (NULL);
	if (!create_array(array, s, c, 0))
		return (NULL);
	free(s);
	return (array);
}
