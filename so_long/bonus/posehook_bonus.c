/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   posehook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:08:36 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 12:59:50 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	lefthook(t_game *g, double time)
{
	static double	local_time = 0;
	static int32_t	current = 0;

	local_time += time;
	if (current >= 3)
		current = 0;
	if (local_time > 0.8)
	{
		put_pixel(g->img[7], g->spr_l->img, current, 0);
		current++;
		local_time -= 0.8;
	}
}

void	righthook(t_game *g, double time)
{
	static double	local_time = 0;
	static int32_t	current = 0;

	local_time += time;
	if (current >= 3)
		current = 0;
	if (local_time > 0.8)
	{
		put_pixel(g->img[8], g->spr_r->img, current, 0);
		current++;
		local_time -= 0.8;
	}
}

void	uphook(t_game *g, double time)
{
	static double	local_time = 0;
	static int32_t	current = 0;

	local_time += time;
	if (current >= 3)
		current = 0;
	if (local_time > 0.8)
	{
		put_pixel(g->img[6], g->spr_u->img, current, 0);
		current++;
		local_time -= 0.8;
	}
}

void	downhook(t_game *g, double time)
{
	static double	local_time = 0;
	static int32_t	current = 0;

	local_time += time;
	if (current >= 3)
		current = 0;
	if (local_time > 0.8)
	{
		put_pixel(g->img[4], g->spr_d->img, current, 0);
		current++;
		local_time -= 0.8;
	}
}
