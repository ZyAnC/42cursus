/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:41:16 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 12:52:34 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	game_error(t_game *g, char *s)
{
	ft_printf("%s", s);
	delete_game(g);
	exit(1);
}

void	delete_image(t_game *g)
{
	int	i;

	i = 0;
	while (i < 16)
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
	if (g->enemy)
		free(g->enemy);
	if (g->spr_h)
		free(g->spr_h);
	if (g->spr_e)
		free(g->spr_e);
	if (g->spr_l)
		free(g->spr_l);
	if (g->spr_u)
		free(g->spr_u);
	if (g->spr_d)
		free(g->spr_d);
	if (g->spr_r)
		free(g->spr_r);
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
