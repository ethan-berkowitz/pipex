/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:07:38 by eberkowi          #+#    #+#             */
/*   Updated: 2024/06/06 10:08:33 by eberkowi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*new_string;
	size_t		new_length;
	int			i;

	if (!s1 || !s2)
		return (NULL);
	new_length = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *)malloc(new_length * sizeof(char) + 1);
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		new_string[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		new_string[i++] = *s2;
		s2++;
	}
	new_string[i] = '\0';
	return (new_string);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!*s1 && !*s2)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	while ((*s1 || *s2) && n-- >= 1)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}