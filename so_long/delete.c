/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:41:16 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/19 20:31:13 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_image(t_game *g)
{
	int	i;

	i = 0;
	while (i < 9)
		mlx_delete_image(g->mlx, g->img[i++]);
	free(g->img);
}

void	delete_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(map[i++]);
	free(map);
	map = NULL;
}

void	delete_game(t_game *g)
{
	if (!g)
		return ;
	if (g->img)
		delete_image(g);
	if (g->map)
		delete_map(g->map, g->height / 64);
	if (g->mlx)
		mlx_terminate(g->mlx);
}

void	quit(t_game *g)
{
	delete_game(g);
	exit(EXIT_SUCCESS);
}
