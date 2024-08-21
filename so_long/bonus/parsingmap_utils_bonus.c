/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:03:29 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 14:54:07 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	ft_freemap(char **map, int rows, int errtype, int errn)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
	map = NULL;
	if (errtype == 1)
		map_error(errn);
}

int	checkwall(char **map, int cols, int rows)
{
	int	i;

	i = 0;
	while (i < cols)
		if (map[0][i++] != '1')
			return (0);
	i = 0;
	while (i < cols)
		if (map[rows - 1][i++] != '1')
			return (0);
	i = 0;
	while (i < rows)
		if (map[i++][0] != '1')
			return (0);
	i = 0;
	while (i < rows)
		if (map[i++][cols - 1] != '1')
			return (0);
	return (1);
}

int	valid_map_value(char c)
{
	return (c == '0' || c == '1'
		|| c == 'C' || c == 'E' || c == 'P' || c == 'M');
}

void	check_playability(char **map, t_cmap cm)
{
	fill_flood(map, &cm);
	if (cm.treasure != cm.co)
		ft_freemap(map, cm.i, 1, 12);
	if (cm.exit != cm.ex)
		ft_freemap(map, cm.i, 1, 13);
	initgame(map, cm);
}

void	count_epcw(char **map, t_cmap cm)
{
	if (cm.ex != 1)
		ft_freemap(map, cm.i, 1, 8);
	if (cm.po != 1)
		ft_freemap(map, cm.i, 1, 9);
	if (cm.co == 0)
		ft_freemap(map, cm.i, 1, 10);
	if (checkwall(map, cm.j, cm.i) == 0)
		ft_freemap(map, cm.i, 1, 11);
	check_playability(map, cm);
}
