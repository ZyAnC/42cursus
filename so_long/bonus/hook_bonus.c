/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:04:07 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/20 20:23:08 by yzheng           ###   ########.fr       */
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
void	step(t_game *g)
{
	char	*nbr;
	char	*heart;
	
	nbr = ft_itoa(++g->movements);
	heart = ft_itoa(g->heart);
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
			nbr,  100, 16);
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
			heart,  216, 16);
	free(heart);
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
	{
		{
		ft_printf("Game over!");
		quit(g);
	}
	}
	if (g->map[g->next.x][g->next.y] == 'E' && g->ex == 1)
	{
		ft_printf("GG!");
		quit(g);
	}
	if(g->map[g->curr.x][g->curr.y] != 'E')
		g->map[g->curr.x][g->curr.y] = '0';
	if(g->map[g->next.x][g->next.y] != 'E')
		g->map[g->next.x][g->next.y] = 'P';
	step(g);
	heart(g);
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

t_point	validmove(int x, int y)
{
	t_point p;
	p.x = x;
	p.y = y;
	return(p);
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
	if(random == -1)
		d = validmove(x - 1, y);
	else if (random == 0)
		d = validmove(x + 1, y);
	else if(random == 1)
		d = validmove(x, y + 1);
	else if(random == 2)
		d = validmove(x, y - 1);

	for(int i = 0;i<g->height /64;i++)
		ft_printf("%s\n",g->map[i]);
	ft_printf("\n");
	if(!ins)
		ft_printf("wtfffff\n\n");
	ft_printf("%d:%d\n",ins->x / 64,ins->y / 64);
	ft_printf("\n");
	
	if (g->map[d.y][d.x] == '0')
	{	
		g->map[y][x] = '0';
		g->map[d.y][d.x] = 'M';
		ins->x = d.x * 64;
		ins->y = d.y * 64;
	}
	if (g->map[d.y][d.x] == 'P')
	{
		ft_printf("game over");
		quit(g);
	}
	
	return ;
}
void	enemyhook(t_game *g)
{
	uint32_t	i;

	i = 0;
	while (i < g->img[13]->count)
	{
		check_enemy(g, &(g->img[13]->instances[i]));
		i++;
	}
	
}


void	loophook(void *param)
{
	t_game	*g;
	double	time;

	g = (t_game *)param;
	time = g->mlx->delta_time;
	static double	local_time = 0;

	local_time += time;
	if (local_time > 0.5)
	{
		enemyhook(g);
		local_time -= 0.5;
	}
	
}