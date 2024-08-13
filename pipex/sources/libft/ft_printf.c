/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:34:37 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/06 16:31:10 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkbase(int fd, char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int), fd));
	else if (c == 's')
		return (ft_putstr(va_arg(ap, char *), fd));
	return (0);
}

static int	pprotection(int fd, char c, va_list ap)
{
	if (c != '%')
		return (checkbase(fd, c, ap));
	else
		return (write(fd, &c, 1));
}

static int	countag(int fd, const char *str, va_list ap, int count)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (!str[i + 1])
				return (-1);
			j = pprotection(fd, str[++i], ap);
			if (j == -1)
				return (-1);
			count += j;
		}
		else
		{
			if (write(fd, &str[i], 1) != 1)
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_printf(int fd, const char *str, ...)
{
	int		count;
	va_list	ap;

	count = 0;
	va_start(ap, str);
	count = countag(fd, str, ap, count);
	va_end(ap);
	return (count);
}
