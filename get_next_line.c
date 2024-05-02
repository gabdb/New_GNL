/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:15:52 by gnyssens          #+#    #+#             */
/*   Updated: 2024/05/03 01:55:10 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// sinon je rajoute une fonction: strdup_till_\n(), ca facilitera tout
char	*dupl_and_adjust_remain(char *remain)
{
	ssize_t	i;
	ssize_t	j;
	char	*new_line;

	new_line = my_strdup(remain); // copie remainder jusqu'à trouver '\0', donc potentiellement plus court que vrai remainder !
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	if ('\n' == new_line[i])
	{
		i++; // i is now the index of first non '\n' character in `remain` and in `new_line`
		j = i; //sauver index i pour adapter `remain` arès
		while (new_line[i] != '\0') // faut bzero tt ce qu'il y a APRES cet index dans `new_line`
			new_line[i++] = '\0';
		i = 0;
		while (remain[j]) // faut bzero tout ce qu'il y a AVANT cet index dans `remain`
			remain[i++] = remain[j++];
		my_bzero(remain, j - i); //jpeux juste while (remain[i] --> remain[i] = '\0')
	}
	else if ('\0' == new_line[i]) //means end of new_line's memory block !
		my_bzero(remain, BUFFER_SIZE + 1);
	return (new_line);
}

ssize_t	extract_buffer(int fd, char *buffer)
{
	
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder = NULL;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0)
		return (NULL);
	remainder = init_remainder(&remainder);
	if (!remainder)
		return (NULL);
	line = dupl_and_adjust_remain(remainder);
	if (!line)
		return (NULL);
	
}

