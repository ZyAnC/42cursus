/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:15:42 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/19 20:50:13 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "./so_long.h"

void	add_image(t_game *g, mlx_image_t *img, int x, int y)
{	
	if (mlx_image_to_window(g->mlx, img, y * 64, x * 64) < 0)
		game_error(g, "Failed to add img to windows");
}

void	ill_background(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->height / 64)
	{
		j = 0;
		while (j < g->width / 64)
		{
			add_image(g, g->img[1], i, j);
			j++;
		}
		i++;
	}
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
			if (g->map[i][j] == 'E')
			{
				add_image(g, g->img[3], i, j);
				g->exit.x = i;
				g->exit.y = j;
			}
			else if (g->map[i][j] == 'P')
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

void	fill_item(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < (g->height / 64))
	{
		j = 0;
		while (j < (g->width / 64))
		{
			if (g->map[i][j] == '1')
				add_image(g, g->img[0], i, j);
			else if (g->map[i][j] == '0')
				add_image(g, g->img[1], i, j);
			else if (g->map[i][j] == 'C')
				add_image(g, g->img[2], i, j);
			j++;
		}
		i++;
	}
	fill_dynamic_items(g);
}

void	game_error(t_game *g, char *s)
{
	ft_printf("%s", s);
	delete_game(g);
	exit(1);
}
