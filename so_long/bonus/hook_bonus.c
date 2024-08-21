/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:04:07 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 12:58:51 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	closehook(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	delete_game(g);
	exit(EXIT_SUCCESS);
}

void	check_enemy(t_game *g, mlx_instance_t *ins)
{
	int		random;
	t_point	d;
	int		x;
	int		y;

	x = ins->x / 64;
	y = ins->y / 64;
	random = ((int)((g->mlx->delta_time) * 40000) % 4) - 1;
	if (random == -1)
		d = validmove(x - 1, y);
	else if (random == 0)
		d = validmove(x + 1, y);
	else if (random == 1)
		d = validmove(x, y + 1);
	else if (random == 2)
		d = validmove(x, y - 1);
	if (g->map[d.y][d.x] == '0')
	{	
		g->map[y][x] = '0';
		g->map[d.y][d.x] = 'M';
		ins->x = d.x * 64;
		ins->y = d.y * 64;
	}
	if (g->map[d.y][d.x] == 'P')
		lose(g);
}

void	enemyhook(t_game *g, double time)
{
	uint32_t		i;
	static double	local_time = 0;

	local_time += time;
	if (local_time > 0.5)
	{
		i = 0;
		while (i < g->img[13]->count)
		{
			check_enemy(g, &(g->img[13]->instances[i]));
			i++;
		}
		local_time -= 0.5;
	}
}

void	loophook(void *param)
{
	t_game	*g;
	double	time;

	g = (t_game *)param;
	time = g->mlx->delta_time;
	enemyhook(g, time);
	spenemyhook(g, time);
	hearthook(g, time);
	lefthook(g, time);
	righthook(g, time);
	uphook(g, time);
	downhook(g, time);
}
