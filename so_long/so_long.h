/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:14:04 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/15 11:16:23 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <fcntl.h>
# include "./src/printf/printf.h"
# include "./src/libft/libft.h"
# include "./src/get_next_line/get_next_line.h"

typedef struct initmap
{
	char	**map;
	int		i;
	int		j;
	int		fd;
	char	*tmp;
}		t_imap;	

typedef struct checkmap
{
	int	i;
	int	j;
	int	ex;
	int	po;
	int	co;
	int	x;
	int	y;
	int treasure;
}		t_cmap;	

void	mapsize(char *filename);
void	error_message(int i);
void	map_error(int i);
int		valid_map_value(char c);
void	ft_freemap(char **map, int rows, int errn);
void	count_epcw(char **map, t_cmap cm);
void	fill_flood(char **map, int **visited, t_cmap cm)
void	fill(char **map, int **visited, t_cmap *cm)
#endif