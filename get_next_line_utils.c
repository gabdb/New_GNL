/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:42:53 by gnyssens          #+#    #+#             */
/*   Updated: 2024/05/03 01:43:34 by gnyssens         ###   ########.fr       */
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
	if (!s || 0 == n)
		return ;
	while (n > 0)
	{
		*s = '\0';
		s++;
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
