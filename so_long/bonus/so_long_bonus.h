/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:14:04 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/20 09:31:19 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include "../src/printf/printf.h"
# include "../src/libft/libft.h"
# include "../src/get_next_line/get_next_line.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		**img;
	t_point			curr;
	t_point			next;
	t_point			exit;
	t_point			*enemy;
	int				width;
	int				height;
	char			**map;
	int				co;
	int				heart;
	int				ex;
	int				em;
	int				movements;
	int				prepose;

}	t_game;

typedef struct initmap
{
	char	**map;
	int		i;
	int		j;
	int		fd;
	char	*tmp;
}	t_imap;	

typedef struct checkmap
{
	int	i;
	int	j;
	int	ex;
	int	po;
	int	co;
	int	em;
	int	x;
	int	y;
	int	treasure;
	int	exit;
}	t_cmap;

void	mapsize(char *filename);
void	error_message(int i);
void	map_error(int i);
void	game_error(t_game *g, char *s);
int		valid_map_value(char c);
void	ft_freemap(char **map, int rows, int errtype, int errn);
void	count_epcw(char **map, t_cmap cm);
void	fill_flood(char **map, t_cmap *cm);
void	fill(char **map, int **visited, t_cmap *cm);
void	initgame(char **map, t_cmap cm);
void	fill_background(t_game *g);
void	fill_item(t_game *g);
void	add_image(t_game *g, mlx_image_t *img, int x, int y);
void	delete_game(t_game *g);
void	closehook(void *param);
void	quit(t_game *g);
void	key_hook(mlx_key_data_t keydata, void *param);
void	loophook(void *param);
#endif