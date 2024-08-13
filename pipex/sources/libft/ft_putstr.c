/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:52:40 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/06 16:30:45 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

int	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (write (fd, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	while (str[i] != '\0')
		i++;
	return (write(fd, str, i));
}
