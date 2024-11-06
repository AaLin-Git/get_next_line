/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:57:10 by akovalch          #+#    #+#             */
/*   Updated: 2024/11/06 18:50:01 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

char	*extract_line(char *buffer)
{
	char	*line;
	char	*start;
	int		length;

	length = ft_strlen(buffer);
	line = ft_calloc((length + 1), sizeof(char));
	if (!line)
		return (ft_free(buffer));
	start = line;
	while (*buffer && *buffer != '\n')
	{
		*line = *buffer;
		line++;
		buffer++;
	}
	if (*buffer == '\n')
	{
		*line = '\n';
		line++;
	}
	*line = '\0';
	return (start);
}

char	*decrease_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
	{
		return (ft_free(buffer));
	}
	new_buffer = ft_calloc((ft_strlen(buffer + i) + 1), sizeof(char));
	if (!new_buffer)
	{
		return (ft_free(buffer));
	}
	while (buffer[i] != '\0')
	{
		new_buffer[j] = buffer[i];
		j++;
		i++;
	}
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

char	*append_buffer(char *basin_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(basin_buffer, read_buffer);
	if (!temp)
	{
		return (ft_free(basin_buffer));
	}
	free(basin_buffer);
	return (temp);
}

char	*read_from_file(char *basin_buffer, int fd)
{
	int			bytes_read;
	char		*cup_buffer;

	cup_buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!cup_buffer)
	{
		free(basin_buffer);
		basin_buffer = NULL;
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(basin_buffer);
			free(cup_buffer);
			return (NULL);
		}
		cup_buffer[bytes_read] = '\0';
		basin_buffer = append_buffer(basin_buffer, cup_buffer);
		if (!basin_buffer)
		{
			return (ft_free(basin_buffer));
		}
		if (ft_strchr(basin_buffer, '\n'))
			break ;
	}
	free(cup_buffer);
	if (bytes_read == 0 && basin_buffer[0] == '\0')
	{
		free(basin_buffer);
		basin_buffer = NULL;
		return (NULL);
	}
	return (basin_buffer);
}

char	*get_next_line( int fd)
{
	static char	*basin_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!basin_buffer)
		basin_buffer = ft_calloc(1, sizeof(char));
	if (!basin_buffer)
		return (NULL);
	basin_buffer = read_from_file(basin_buffer, fd);
	if (!basin_buffer)
		return (NULL);
	line = extract_line(basin_buffer);
	if (!line)
		return (NULL);
	basin_buffer = decrease_buffer(basin_buffer);
	return (line);
}
