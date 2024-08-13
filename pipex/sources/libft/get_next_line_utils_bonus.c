/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:02:41 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/04 17:52:59 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_getline(char *src)
{
	int		i;
	char	*line;

	i = 0;
	if (!src[i])
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	line = (char *)malloc((i + 1 + (src[i] == '\n')));
	if (!line)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		line[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		line[i] = src[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

size_t	g_ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*g_ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*g_ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	str = (char *)malloc(((ft_strlen(s1)) + (ft_strlen(s2)) + 1));
	if (!str)
		return (ft_free(&s1));
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	ft_free(&s1);
	return (str);
}

char	*getnewline(char *str)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (ft_free(&str));
	newstr = (char *)malloc((ft_strlen(str) - i + 1));
	if (!newstr)
		return (ft_free(&str));
	i++;
	j = 0;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	ft_free(&str);
	return (newstr);
}
