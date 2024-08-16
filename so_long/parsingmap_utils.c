/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:03:29 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/15 12:27:25 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_freemap(char **map, int rows, int errn)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
	map = NULL;
	map_error(errn);
}

int	checkwall(char *s1, char *s2, int cols)
{
	int	i;
	
	i = 0;
	while (i < cols)
	{
	
		if (s1[i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < cols)
	{
		
		if (s2[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	valid_map_value(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}


void	check_playability(char **map, t_cmap cm)
{
		
		fill_flood(map, &cm);
		for(int i = 0;i<cm.i;i++)
		{
			ft_printf("%s\n",map[i]);
		}
		ft_printf("%d",cm.treasure);
}

void	count_epcw(char **map, t_cmap cm)
{
	if (cm.ex != 1)
		ft_freemap(map, cm.i, 8);
	if (cm.po != 1)
		ft_freemap(map, cm.i, 9);
	if (cm.co == 0)
		ft_freemap(map, cm.i, 10);
	if (checkwall(map[0], map[cm.i - 1],cm.j) == 0)
		ft_freemap(map, cm.i, 11);
	check_playability(map, cm);
}
