/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:15:52 by gnyssens          #+#    #+#             */
/*   Updated: 2024/05/06 16:22:45 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	end_of_line(char *line)
{
	ssize_t	i;

	i = 0;
	while (line[i])
	{
		if ('\n' == line[i])
			return (i);
		i++;
	}
	i = 0;
	return (-1);
}

char	*dupl_and_adjust_remain(char *remain)
{
	ssize_t	i;
	ssize_t	j;
	char	*new_line;

	new_line = myy_strdup(remain);
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	if ('\n' == new_line[i])
	{
		j = i + 1;
		while (new_line[++i] != '\0')
			new_line[i] = '\0';
		i = 0;
		while (j < BUFFER_SIZE + 1)
			remain[i++] = remain[j++];
		my_bzero(remain + i, BUFFER_SIZE + 1 - i);
	}
	else if ('\0' == new_line[i])
		my_bzero(remain, BUFFER_SIZE + 1);
	return (new_line);
}

char	extract_buffer(int fd, char *buffer)
{
	ssize_t	count;
	ssize_t	i;

	my_bzero(buffer, BUFFER_SIZE + 1);
	count = read(fd, buffer, BUFFER_SIZE);
	if (count < 0)
		return ('e');
	else if (count == 0)
		return ('\0');
	i = 0;
	while (i < count)
	{
		if ('\n' == buffer[i])
			return ('\n');
		i++;
	}
	return ('c');
}

ssize_t	manage_extraction(int fd, char *buf, char **line)
{
	char	check;
	ssize_t	i;

	check = 'c';
	while (check == 'c')
	{
		check = extract_buffer(fd, buf);
		if (check == 'c')
			*line = my_strjoin(*line, buf);
		if (!(*line))
			return (-1);
	}
	if (check == '\n')
	{
		*line = my_strjoin(*line, buf);
		if (!(*line))
			return (-1);
		i = end_of_line(*line) + 1;
		while ((*line)[i] != 0)
			(*line)[i++] = '\0';
		return (0);
	}
	if (check == 'e')
		return (free(*line), -1);
	return (2);
}

char	*get_next_line(int fd)
{
	ssize_t		i;
	ssize_t		check;
	char		*line;
	static char	*remainder = NULL;
	char		*buffer;

	buffer = NULL;
	remainder = init_remainder(remainder, &buffer);
	if (!remainder || fd < 0)
		return (free(buffer), NULL);
	line = dupl_and_adjust_remain(remainder);
	if (!line)
		return (free(remainder),remainder = NULL,free(buffer),NULL);
	if (end_of_line(line) >= 0)
		return (free(buffer), buffer = NULL, line);
	check = manage_extraction(fd, buffer, &line);
	if (check == -1)
		return (free(remainder),remainder = NULL,free(buffer),NULL);
	else if (check == 0)
	{
		i = end_of_line(buffer);
		while (buffer[++i] != '\0')
			remainder[check++] = buffer[i];
		my_bzero(remainder + check, BUFFER_SIZE + 1 - check);
	}
	if (*line == '\0')
		return (free(remainder),remainder = NULL,free(line),free(buffer), NULL);
	return (free(buffer), line);
}

/*
int main() {
    int fd;
    char *line;

    fd = open("tekst.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return (1);
    }
	
	int i = 0;
	while (i < 15) // && line != NULL)
	{
		line = get_next_line(fd);
        printf("%d'th line: %s", i + 1, line);  // Print each line as it's read
		free(line); // Don't forget to free memory!
		i++;
    }

    close(fd);
    return (0);
} 
*/