/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:15:52 by gnyssens          #+#    #+#             */
/*   Updated: 2024/05/04 03:17:59 by gnyssens         ###   ########.fr       */
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
	return (0);
}

// sinon je rajoute une fonction: strdup_till_\n(), ca facilitera tout
char	*dupl_and_adjust_remain(char *remain)
{
	ssize_t	i;
	ssize_t	j;
	char	*new_line;

	//printf("\n\nremain: %s\n", remain);
	new_line = my_strdup(remain); // copie remainder jusqu'à trouver '\0', donc potentiellement plus court que vrai remainder !
	//printf("devrait etre pareil: %s\n\n", new_line);
	if (!new_line)
		return (NULL);
	i = 0;
	while (new_line[i] && new_line[i] != '\n')
		i++;
	if ('\n' == new_line[i])
	{
		j = i + 1; //sauver index i pour adapter `remain` arès
		while (new_line[++i] != '\0') // faut bzero tt ce qu'il y a APRES cet index dans `new_line`
			new_line[i] = '\0';
		i = 0;
		while (j <= BUFFER_SIZE + 1) // faut bzero tout ce qu'il y a AVANT cet index dans `remain`
			remain[i++] = remain[j++];
		my_bzero(remain, j - i);
	}
	else if ('\0' == new_line[i]) //means end of new_line's memory block !
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
		return ('e'); // 'e' means ERROR
	else if (count == 0)
		return ('\0'); // \0 for end of file
	i = 0;
	while (i < count)
	{
		if ('\n' == buffer[i])
			return ('\n'); // \n for end of line
		i++;
	}
	return ('c'); //no \n nor \0, so 'c' for CONTINUE
}

ssize_t	manage_extraction(int fd, char *buf, char **line)
{
	char	check;

	check = 'c';
	while (check == 'c')
	{
		check = extract_buffer(fd, buf);
		if (check == 'c')
		{
			*line = my_strjoin(*line, buf);
			if (!(*line))
				return (-1);
		}
	}
	if (check == '\0')
		return (free(*line), *line = NULL, 1); //file fini, extract a lu 0 char's...
	else if (check == '\n')
	{
		*line = my_strjoin(*line, buf);
		if (!(*line))
			return (-1);
		return (0);
	}
	return (2);
}

char	*get_next_line(int fd)
{
	ssize_t		i;
	ssize_t		check;
	char		*line;
	static char	*remainder = NULL;
	char		buffer[BUFFER_SIZE + 1];

	remainder = init_remainder(&remainder);
	if (!remainder || fd < 0)
		return (NULL);
	//printf("\n___%s___\n", remainder);
	line = dupl_and_adjust_remain(remainder);
	//printf("line after dup:  %s\n", line);
	if (!line)
		return (free(remainder), remainder = NULL, NULL);
	if (end_of_line(line) > 0) //je check pas si line contient '\0'
		return (line);
	check = manage_extraction(fd, buffer, &line);
	if (check == -1 || check == 1) // erreur dans le process || fin de fichier
		return (free(remainder), remainder = NULL, NULL);
	else if (check == 0)
	{	//ici faut encore bzero line apres \n !!!!!!!!!!
		i = end_of_line(buffer);
		while (buffer[++i] != '\0')
			remainder[check++] = buffer[i];
		my_bzero(remainder + check, BUFFER_SIZE - check);
	}
	//if (my_strlen(line) == 0)
	//	return (free(line), line = NULL, NULL);
	//printf("line avant return: %s\n", line);
	return (line);
}

int main() {
    int fd;
    char *line;

    fd = open("tekst.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return (1);
    }
	
	int i = 0;
	while (i < 6 && line != NULL) {
		line = get_next_line(fd);
        printf("%d'th line: %s\n", i+1, line);  // Print each line as it's read
		free(line); // Don't forget to free memory!
		i++;
    }

    close(fd);
    return (0);
} 

