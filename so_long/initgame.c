/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:40 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 14:41:58 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

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
	if (!mlx_resize_image(img, 64, 64))
		game_error(g, "Failed to resize image");
	return (img);
}

void	save_img(t_game *g)
{
	g->img = malloc(9 * sizeof(mlx_image_t));
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
}

void	initgame(char **map, t_cmap cm)
{
	t_game	game;

	game.map = map;
	game.width = cm.j * 64;
	game.height = cm.i * 64;
	game.co = cm.co;
	game.ex = 0;
	game.heart = 0;
	game.movements = 0;
	game.prepose = 4;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game.mlx = mlx_init(game.width, game.height, "so_long", true);
	if (!game.mlx)
		game_error(&game, "Allocated game failed");
	save_img(&game);
	fill_background(&game);
	fill_item(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_close_hook(game.mlx, closehook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}
