/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:30:00 by akovalch          #+#    #+#             */
/*   Updated: 2024/11/11 14:30:06 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*next_line;
	int i = 0;
	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		next_line = get_next_line(fd);
		i++;
		if (next_line == NULL)
			break ;
		printf("[%d]   %s", i, next_line);
		free(next_line);
		next_line = NULL;
	}
	close(fd);
	return (0);
}