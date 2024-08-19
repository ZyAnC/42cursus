/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:04:07 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/19 21:04:41 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

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
	if (g->map[g->next.x][g->next.y] == 'E' && g->ex == 1)
	{
		ft_printf("GG!");
		quit(g);
	}
	g->map[g->curr.x][g->curr.y] = '0';
	g->map[g->next.x][g->next.y] = 'P';
	ft_printf("Movements: %u, hearts: %u\n", ++g->movements, g->heart);
	posture(i, g);
	g->curr.x = g->next.x;
	g->curr.y = g->next.y;
}

void	closehook(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	delete_game(g);
	exit(EXIT_SUCCESS);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		quit(g);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		g->next = (t_point){g->curr.x, g->curr.y - 1};
		move(7, g);
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		g->next = (t_point){g->curr.x, g->curr.y + 1};
		move(8, g);
	}
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		g->next = (t_point){g->curr.x - 1, g->curr.y};
		move(6, g);
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		g->next = (t_point){g->curr.x + 1, g->curr.y};
		move(4, g);
	}
}
