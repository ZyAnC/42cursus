/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:40 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 12:50:40 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

static mlx_image_t	*load_img(t_game *g, const char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		game_error(g, "Failed to load texture");
	img = mlx_texture_to_image(g->mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		game_error(g, "Failed to load imgage");
	if (ft_strncmp(path, "./gfx/win.png", 13)
		&& ft_strncmp(path, "./gfx/lose.png", 14))
	{	
		if (!mlx_resize_image(img, 64, 64))
			game_error(g, "Failed to resize image");
	}
	return (img);
}

static t_sprite	*load_spr(t_game *g, char *path, uint32_t rows, uint32_t cols)
{
	mlx_texture_t	*tex;
	t_sprite		*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	tex = mlx_load_png(path);
	if (!tex)
		game_error(g, "Failed to load sprite.");
	sprite->img = mlx_texture_to_image(g->mlx, tex);
	mlx_delete_texture(tex);
	if (!sprite->img)
		game_error(g, "Allocation error on read texture.");
	if (!mlx_resize_image(sprite->img, 64 * cols, 64 * rows))
		game_error(g, "Failed to resize image.");
	sprite->rows = rows;
	sprite->cols = cols;
	return (sprite);
}

void	save_img(t_game *g)
{
	g->img = malloc(16 * sizeof(mlx_image_t));
	if (!g->img)
		game_error(g, "Allocated failed");
	g->img[0] = load_img(g, "./gfx/wall.png");
	g->img[1] = load_img(g, "./gfx/floor.png");
	g->img[2] = load_img(g, "./gfx/co.png");
	g->img[3] = load_img(g, "./gfx/flag.png");
	g->img[4] = load_img(g, "./gfx/player.png");
	g->img[5] = load_img(g, "./gfx/exit.png");
	g->img[6] = load_img(g, "./gfx/up.png");
	g->img[7] = load_img(g, "./gfx/left.png");
	g->img[8] = load_img(g, "./gfx/right.png");
	g->img[9] = NULL;
	g->img[10] = NULL;
	g->img[11] = NULL;
	g->img[12] = NULL;
	g->img[13] = load_img(g, "./gfx/enemy.png");
	g->img[14] = load_img(g, "./gfx/lose.png");
	g->img[15] = load_img(g, "./gfx/win.png");
	g->spr_e = load_spr(g, "./gfx/spenemy.png", 1, 7);
	g->spr_h = load_spr(g, "./gfx/coin.png", 1, 11);
	g->spr_l = load_spr(g, "./gfx/spleft.png", 1, 3);
	g->spr_u = load_spr(g, "./gfx/spup.png", 1, 3);
	g->spr_d = load_spr(g, "./gfx/spdown.png", 1, 3);
	g->spr_r = load_spr(g, "./gfx/spright.png", 1, 3);
}

void	initdata(t_game *game, t_cmap cm, char **map)
{
	game->map = map;
	game->width = cm.j * 64;
	game->height = cm.i * 64;
	game->co = cm.co;
	game->ex = 0;
	game->heart = 0;
	game->status = 1;
	game->movements = 0;
	game->prepose = 4;
	game->em = cm.em;
}

void	initgame(char **map, t_cmap cm)
{
	t_game	game;

	initdata(&game, cm, map);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game.mlx = mlx_init(game.width, game.height, "so_long", true);
	if (!game.mlx)
		game_error(&game, "Allocated game failed");
	save_img(&game);
	fill_background(&game);
	fill_item(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_close_hook(game.mlx, closehook, &game);
	mlx_loop_hook(game.mlx, loophook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}
