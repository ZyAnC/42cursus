/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:02:27 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/06 16:39:05 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static char	*getbuffer(int fd,	char *line)
{
	char		*buffer;
	int			bytesread;

	buffer = malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&line));
	bytesread = 1;
	while (!(g_ft_strchr(line, '\n')) && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread > 0)
		{
			buffer[bytesread] = '\0';
			line = g_ft_strjoin (line, buffer);
		}
	}
	free(buffer);
	if (bytesread == -1)
		return (ft_free(&line));
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*bufferline[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	bufferline[fd] = getbuffer(fd, bufferline[fd]);
	if (!bufferline[fd])
		return (NULL);
	line = ft_getline(bufferline[fd]);
	if (!line)
		return (ft_free(&bufferline[fd]));
	bufferline[fd] = getnewline(bufferline[fd]);
	return (line);
}
