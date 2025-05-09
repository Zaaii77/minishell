/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:19:25 by acaes             #+#    #+#             */
/*   Updated: 2025/01/06 12:20:38 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gnl.h"
#include "../../inc/libft.h"

char	*ft_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	*fill_line(int fd, char *left)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	b_read;
	char	*temp;

	if (!left)
		left = ft_strdup("");
	if (!left)
		return (NULL);
	while (!ft_strchr(left, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (ft_free(&left));
		if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		temp = ft_strjoin(left, buffer);
		if (!temp)
			return (ft_free(&left));
		free(left);
		left = temp;
	}
	return (left);
}

char	*set_line(char *line)
{
	char	*extracted_line;
	ssize_t	l;

	if (!line || *line == '\0')
		return (NULL);
	l = 0;
	while (line[l] && line[l] != '\n')
		l++;
	if (line[l] == '\n')
		l++;
	extracted_line = ft_substr(line, 0, l);
	return (extracted_line);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX] = {NULL};
	char		*line;
	char		*tmp;

	if (fd < 0 || fd >= FD_MAX)
		return (NULL);
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= MAXINT)
		return (NULL);
	stash[fd] = fill_line(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = set_line(stash[fd]);
	if (!line)
		return (ft_free(&stash[fd]));
	tmp = stash[fd];
	stash[fd] = ft_strdup(stash[fd] + ft_strlen(line));
	if (!stash[fd])
		return (ft_free(&line));
	free(tmp);
	return (line);
}
/*
#include <stdio.h>

int main()
{
    const char *files[] = {"file1.txt", "file2.txt"};
    int fd[2];  // Tableau de descripteurs de fichier
    char *line1, *line2;
    size_t i;

    i = 0;
    while (i < sizeof(files) / sizeof(files[0]))
    {
        fd[i] = open(files[i], O_RDONLY);
        if (fd[i] < 0)
        {
            perror("Error opening file");
            return (1);
        }
        i++;
    }
    line1 = get_next_line(fd[0]);
    line2 = get_next_line(fd[1]);
    while (line1 || line2)
    {
        if (line1)
        {
            printf("file1: %s", line1);
            free(line1);
            line1 = get_next_line(fd[0]);
        }
        if (line2)
        {
            printf("file2: %s", line2);
            free(line2);
            line2 = get_next_line(fd[1]);
        }
    }
    close(fd[0]);
    close(fd[1]);
    return (0);
}
*/
