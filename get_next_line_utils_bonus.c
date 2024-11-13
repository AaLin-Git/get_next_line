/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalch <akovalch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:40:21 by akovalch          #+#    #+#             */
/*   Updated: 2024/11/12 15:40:30 by akovalch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (*str)
	{
		counter++;
		str++;
	}
	return (counter);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*flag;

	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	flag = str;
	while (*s)
	{
		*str = *s;
		s++;
		str++;
	}
	*str = '\0';
	return ((char *)flag);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*start;

	if (!s1 || !s2)
		return (0);
	newstr = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	start = newstr;
	while (*s1)
	{
		*newstr = *s1;
		s1++;
		newstr++;
	}
	while (*s2)
	{
		*newstr = *s2;
		s2++;
		newstr++;
	}
	*newstr = '\0';
	return (start);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	i = 0;
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len < (start + len))
		len = s_len - start;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
