/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:03:03 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/15 12:22:55 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**init_array(int rows, int cols)
{
	char	**map;
	int		i;
	int		j;

	map = malloc(rows * sizeof(char *));
	if (!map)
		error_message(5);
	i = 0;
	while (i < rows)
	{
		map[i] = malloc(cols + 1 * sizeof(char));
		if (!map[i])
		{
			j = 0;
			while (j <= i)
				free(map[j++]);
			free(map);
			error_message(5);
		}
		i++;
	}
	return (map);
}

char	**init_map(int rows, int cols, char *filename)
{
	t_imap	im;

	im.map = init_array(rows, cols);
	im.fd = open(filename, O_RDONLY);
	if (im.fd == -1)
		ft_freemap(im.map, rows, 4);
	im.i = 0;
	while (1)
	{
		im.tmp = get_next_line(im.fd);
		if (!im.tmp)
			break ;
		im.j = -1;
		while (im.tmp[++im.j] && valid_map_value(im.tmp[im.j]))
			im.map[im.i][im.j] = im.tmp[im.j];
		if (im.j != cols)
			map_error(7);
		im.map[im.i][im.j] = '\0';
		free(im.tmp);
		im.i++;
	}
	close(im.fd);
	if (im.i != rows)
		error_message(5);
	return (im.map);
}


void	check_map(char **map, int rows, int cols)
{
	t_cmap	cm;

	cm.ex = 0;
	cm.i = -1;
	cm.po = 0;
	cm.co = 0;
	while (++cm.i < rows)
	{
		cm.j = 0;
		while (cm.j < cols)
		{
			if (map[cm.i][cm.j] == 'P')
			{
				cm.po++;
				cm.x = cm.i;
				cm.y = cm.j;
			}
			if (map[cm.i][cm.j] == 'E')
				cm.ex++;
			if (map[cm.i][cm.j] == 'C')
				cm.co++;
			cm.j++;
		}
	}
	count_epcw(map,cm);
}

void	mapsize(char *filename)
{
	int		fd;
	int		rows;
	int		cols;
	char	*tmp;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_message(4);
	tmp = get_next_line(fd);
	if(!tmp)
		error_message(5);
	cols = ft_strlen(tmp) - 1;
	rows = 0;
	while (tmp != NULL)
	{
		rows++;
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	map = init_map(rows, cols, filename);
	check_map(map, rows, cols);
}
