/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:06:25 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/20 14:46:18 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	fill(char **map, int **visited, t_cmap *cm)
{
	int	original_x;
	int	original_y;

	if (cm->x < 0 || cm->x >= cm->i || cm->y < 0 || cm->y >= cm->j 
		|| map[cm->x][cm->y] == '1' || visited[cm->x][cm->y])
		return ;
	if (map[cm->x][cm->y] == 'C')
		cm->treasure++;
	if (map[cm->x][cm->y] == 'E')
		cm->exit++;
	visited[cm->x][cm->y] = 1;
	original_x = cm->x;
	original_y = cm->y;
	cm->x = original_x - 1;
	fill(map, visited, cm);
	cm->x = original_x + 1;
	fill(map, visited, cm);
	cm->x = original_x;
	cm->y = original_y - 1;
	fill(map, visited, cm);
	cm->y = original_y + 1;
	fill(map, visited, cm);
	cm->x = original_x;
	cm->y = original_y;
}

void	fill_flood(char **map, t_cmap *cm)
{
	int	**visited;
	int	i;

	cm->exit = 0;
	cm->treasure = 0;
	visited = (int **)malloc(cm->i * sizeof(int *));
	if (!visited)
		return ;
	i = 0;
	while (i < cm->i)
	{
		visited[i] = (int *)ft_calloc(cm->j, sizeof(int));
		if (!visited[i++])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return ;
		}
	}
	fill(map, visited, cm);
	i = 0;
	while (i < cm->i)
		free(visited[i++]);
	free(visited);
}
