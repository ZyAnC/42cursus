/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spirit_hook_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:09:48 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 12:58:55 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int32_t	get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*start;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	start = image->pixels + (y * image->width + x) * sizeof(int32_t);
	return (get_rgba(*(start),
			*(start + 1),
			*(start + 2),
			*(start + 3)));
}

void	put_pixel(mlx_image_t *img, mlx_image_t *spr, uint32_t x, uint32_t y)
{
	uint32_t		w;
	uint32_t		h;

	h = 0;
	while (h < img->height)
	{
		w = 0;
		while (w < img->width)
		{
			mlx_put_pixel(img, w, h,
				get_pixel(spr, x * 64 + w, y * 64 + h));
			w++;
		}
		h++;
	}
}

void	hearthook(t_game *g, double time)
{
	static double	local_time = 0;
	static int32_t	current = 0;

	local_time += time;
	if (current >= 4)
		current = 0;
	if (local_time > 0.4)
	{
		put_pixel(g->img[2], g->spr_h->img, current, 0);
		current++;
		local_time -= 0.4;
	}
}

void	spenemyhook(t_game *g, double time)
{
	static double	local_time = 0;
	static int32_t	current = 0;

	local_time += time;
	if (current >= 7)
		current = 0;
	if (local_time > 0.6)
	{
		put_pixel(g->img[13], g->spr_e->img, current, 0);
		current++;
		local_time -= 0.6;
	}
}
