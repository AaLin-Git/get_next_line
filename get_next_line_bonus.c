/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:44:29 by akovalch          #+#    #+#             */
/*   Updated: 2024/11/12 16:48:58 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*read_line(int fd, char *buffer, char *storage)
{
	ssize_t		bytes;
	char		*temp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free(&storage));
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (!storage)
			storage = ft_strdup("");
		temp = storage;
		storage = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (storage);
}

char	*split_storage(char **line)
{
	unsigned int	i;
	char			*storage;
	char			*temp;

	i = 0;
	while ((*line)[i] != '\n' && (*line)[i] != '\0')
		i++;
	if ((*line)[i] == '\0' || (*line)[1] == '\0' || (*line)[i + 1] == '\0')
		return (NULL);
	temp = *line;
	*line = ft_substr(temp, 0, (i + 1));
	if (!*line)
		return (ft_free(&temp));
	storage = ft_substr(temp, (i + 1), (ft_strlen(temp) - i));
	free(temp);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[2048];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&storage[fd]));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&storage[fd]));
	line = read_line(fd, buffer, storage[fd]);
	free(buffer);
	if (!line)
	{
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = split_storage(&line);
	return (line);
}
