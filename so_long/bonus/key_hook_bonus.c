/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:17:10 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 12:38:49 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

static void	change_co(t_game *g)
{
	size_t	i;

	i = 0;
	while (i < g->img[2]->count)
	{
		if (g->img[2]->instances[i].x == (int)(g->next.y * 64)
			&& g->img[2]->instances[i].y == (int)(g->next.x * 64))
		{
			g->img[2]->instances[i].enabled = false;
			break ;
		}
		i++;
	}
	if (g->heart == g->co)
	{	
		g->ex = 1;
		i = g->img[3]->instances[0].y;
		g->img[3]->instances[0].enabled = false;
		add_image(g, g->img[5], i, g->img[3]->instances[0].x);
		g->img[5]->instances[0].x = g->img[3]->instances[0].x;
		g->img[5]->instances[0].y = g->img[3]->instances[0].y;
	}
}

static void	posture(int i, t_game *g)
{
	if (g->prepose != i)
	{
		g->img[g->prepose]->instances[0].enabled = false;
		g->prepose = i;
	}
	if (i == 4)
	{	
		g->img[i]->instances[0].enabled = true;
		g->img[i]->instances[0].x = g->next.y * 64;
		g->img[i]->instances[0].y = g->next.x * 64;
	}
	else
	{
		if (g->img[i]->count == 0)
			add_image(g, g->img[i], g->next.y * 64, g->next.x * 64);
		g->img[i]->instances[0].enabled = true;
		g->img[i]->instances[0].x = g->next.y * 64;
		g->img[i]->instances[0].y = g->next.x * 64;
	}
}

static void	move(int i, t_game *g)
{
	if (g->map[g->next.x][g->next.y] == '1' ||
	g->next.x >= g->height / 64 || g->next.y >= g->width / 64)
		return ;
	if (g->map[g->next.x][g->next.y] == 'C')
	{	
		g->heart++;
		g->map[g->next.x][g->next.y] = '0';
		change_co(g);
	}
	if (g->map[g->next.x][g->next.y] == 'M')
		lose(g);
	if (g->map[g->next.x][g->next.y] == 'E' && g->ex == 1)
		win(g);
	if (g->map[g->curr.x][g->curr.y] != 'E')
		g->map[g->curr.x][g->curr.y] = '0';
	if (g->map[g->next.x][g->next.y] != 'E')
		g->map[g->next.x][g->next.y] = 'P';
	step(g);
	heart(g);
	posture(i, g);
	g->curr.x = g->next.x;
	g->curr.y = g->next.y;
}

static void	gomove(int i, t_game *g)
{
	if (i == 7)
		g->next = (t_point){g->curr.x, g->curr.y - 1};
	else if (i == 8)
		g->next = (t_point){g->curr.x, g->curr.y + 1};
	else if (i == 6)
		g->next = (t_point){g->curr.x - 1, g->curr.y};
	else if (i == 4)
		g->next = (t_point){g->curr.x + 1, g->curr.y};
	move(i, g);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		quit(g);
	if (g->status == 0 && keydata.action == MLX_PRESS)
		quit(g);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		gomove(7, g);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		gomove(8, g);
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		gomove(6, g);
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		gomove(4, g);
}
