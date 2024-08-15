/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 10:13:28 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/15 11:48:05 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_message(int i)
{
	if (!i)
		ft_printf("Miss mapfile");
	else if (i == 2)
		ft_printf("Too many arguments");
	else if (i == 3)
		ft_printf("Wrong map format");
	else if (i == 4)
		ft_printf("Failed to open file");
	else if (i == 5)
		ft_printf("Allocate failed");
	else if (i == 6)
		ft_printf("Read failed");
	exit(1);
}

void	map_error(int	i)
{
	if (i == 7)
		ft_printf("Invalid map value or the map is not rectangular");
	else if (i == 8)
		ft_printf("Map needs 1 exit");
	else if (i == 9)
		ft_printf("Map needs 1 start position");
	else if (i == 10)
		ft_printf("Need Treasure");
	else if (i == 11)
		ft_printf("Bad Wall");
	exit(1);
}
void	checkmapname(char *filename)
{
	char	*result;

	result = ft_strnstr(filename, ".ber", ft_strlen(filename));
	if (result != NULL)
	{
		if ((result + 3) == (filename + ft_strlen(filename) - 1))
		{
			mapsize(filename);
		}
	}
	else
		error_message(3);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		error_message(0);
	else if (ac == 2)
		checkmapname(av[1]);
	else
		error_message(2);
}
