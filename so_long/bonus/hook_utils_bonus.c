/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:14:45 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 12:38:30 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	win(t_game *g)
{
	if (!mlx_resize_image(g->img[15], g->width, g->height))
		game_error(g, "Failed to resize image.");
	if (mlx_image_to_window(g->mlx, g->img[15], 0, 0) < 0)
		game_error(g, "cannot draw image to windows.");
	g->status = 0;
}

void	lose(t_game *g)
{	
	if (!mlx_resize_image(g->img[14], g->width, g->height))
		game_error(g, "Failed to resize image.");
	if (mlx_image_to_window(g->mlx, g->img[14], 0, 0) < 0)
		game_error(g, "cannot draw image to windows.");
	g->status = 0;
}

t_point	validmove(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	step(t_game *g)
{
	char	*nbr;

	nbr = ft_itoa(++g->movements);
	if (g->img[10] == NULL)
	{
		g->img[9] = mlx_put_string(g->mlx, "Steps: ", 16, 16);
		g->img[10] = mlx_put_string(g->mlx,
				nbr, 100, 16);
		free(nbr);
		return ;
	}
	mlx_delete_image(g->mlx, g->img[10]);
	g->img[10] = mlx_put_string(g->mlx,
			nbr, 100, 16);
	free(nbr);
}

void	heart(t_game *g)
{
	char	*heart;

	heart = ft_itoa(g->heart);
	if (g->img[12] == NULL)
	{
		g->img[11] = mlx_put_string(g->mlx, "HeartS: ", 132, 16);
		g->img[12] = mlx_put_string(g->mlx,
				heart, 216, 16);
		free(heart);
		return ;
	}
	mlx_delete_image(g->mlx, g->img[12]);
	g->img[12] = mlx_put_string(g->mlx,
			heart, 216, 16);
	free(heart);
}
