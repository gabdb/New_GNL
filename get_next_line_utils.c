/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:42:53 by gnyssens          #+#    #+#             */
/*   Updated: 2024/05/04 03:16:15 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	my_strlen(char *str)
{
	ssize_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*init_remainder(char **remain)
{
	if (*remain != NULL)
		return (*remain);
	*remain = (char *)malloc(BUFFER_SIZE + 1);
	if (!(*remain))
		return (NULL);
	my_bzero(*remain, BUFFER_SIZE + 1);
	return (*remain);
}

void	my_bzero(char *s, ssize_t n)
{
	ssize_t	i;

	if (!s || 0 == n)
		return ;
	i = 0;
	while (n > 0 && s[i])
	{
		s[i] = '\0';
		i++;
		n--;
	}
}

char	*my_strdup(char *str)
{
	ssize_t	len;
	ssize_t	i;
	char    *ptr;

	if (!str)
		return (NULL);
	len = my_strlen(str);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	my_bzero(ptr + i, len + 1 - i);
	return (ptr);
}

char	*my_strjoin(char *s1, char *s2)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	len = my_strlen(s1) + my_strlen(s2);
	result = (char *)malloc(len + 1);
	if (!result)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j]) // && s2[j] != '\n')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (free(s1), result);
}
