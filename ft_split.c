/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:44:03 by eberkowi          #+#    #+#             */
/*   Updated: 2024/06/11 11:42:17 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_count_words(char const *s, char c)
{
	int	num_words;

	num_words = 0;
	while (*s)
	{
		if (*s != c)
		{
			num_words++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (num_words);
}

static int	ft_word_len(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != c && *s)
	{
		count++;
		s++;
	}
	return (count);
}

static char	*ft_place_word(char *new_array, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		new_array[i] = *s;
		i++;
		s++;
	}
	new_array[i] = '\0';
	return (new_array);
}

static char	**ft_free_all(char **new_array, int i)
{
	while (i >= 0)
	{
		free(new_array[i]);
		i--;
	}
	free(new_array);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**new_array;
	int		i;

	if (!s)
		return (NULL);
	new_array = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			new_array[i] = (char *)malloc(ft_word_len(s, c) + 1);
			if (new_array[i] == NULL)
				return (ft_free_all(new_array, i));
			ft_place_word(new_array[i++], s, c);
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	new_array[i] = 0;
	return (new_array);
}