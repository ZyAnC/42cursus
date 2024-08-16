/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:06:25 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/15 11:06:27 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void fill(char **map, int **visited, t_cmap *cm)
{
    int original_x;
    int original_y;
    if (cm->x < 0 || cm->x >= cm->i || cm->y < 0 || cm->y >= cm->j || map[cm->x][cm->y] == '1' || visited[cm->x][cm->y])
        return ;
    if (map[cm->x][cm->y] == 'C')
        cm->treasure++;
    visited[cm->x][cm->y] = 1;
    original_x = cm->x;
    original_y = cm->y;
    cm->x = original_x - 1;
    fill(map, cm);
    cm->x = original_x + 1;
    fill(map, cm);
    cm->x = original_x; 
    cm->y = original_y - 1;
    fill(map, cm);
    cm->y = original_y + 1; 
    fill(map, cm);
}

void fill_flood(char **map, int **visited, t_cmap cm)
{
    cm.treasure = 0; 
    fill(map, visited, &cm);  
	ft_printf("%d",cm.treasure);
}
