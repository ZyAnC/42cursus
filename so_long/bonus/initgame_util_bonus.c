/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame_util_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:15:42 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 14:56:49 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "./so_long_bonus.h"

void	fill_background(t_game *g)
{
	int		i;
	int		j;
	t_point	*p;

	i = 0;
	while (i < g->height / 64)
	{
		j = 0;
		while (j < g->width / 64)
			add_image(g, g->img[1], i, j++);
		i++;
	}
	p = (t_point *)malloc((g->em) * sizeof(t_point));
	if (!p)
		game_error(g, "Couldn't apply space for enemy");
	g->enemy = p;
}

static void	fill_dynamic_items(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < (g->height / 64))
	{
		j = 0;
		while (j < (g->width / 64))
		{
			if (g->map[i][j] == 'P')
			{
				g->curr.x = i;
				g->curr.y = j;
				add_image(g, g->img[4], i, j);
			}
			j++;
		}
		i++;
	}
}

static void	save_enemy(int k, t_game *g, int x, int y)
{
	add_image(g, g->img[13], x, y);
	k = 0;
	g->enemy[k].x = x;
	g->enemy[k].y = y;
}

static void	stupidnorminnette(t_game *g, int i, int j)
{
	add_image(g, g->img[3], i, j);
	g->exit.x = i;
	g->exit.y = j;
}

void	fill_item(t_game *g)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = -1;
	while (++i < (g->height / 64))
	{
		j = -1;
		while (++j < (g->width / 64))
		{
			if (g->map[i][j] == '1')
				add_image(g, g->img[0], i, j);
			else if (g->map[i][j] == 'M')
				save_enemy(k, g, i, j);
			else if (g->map[i][j] == 'C')
				add_image(g, g->img[2], i, j);
			else if (g->map[i][j] == 'E')
				stupidnorminnette(g, i, j);
		}
	}
	fill_dynamic_items(g);
}
