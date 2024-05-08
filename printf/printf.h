/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:52:34 by yzheng            #+#    #+#             */
/*   Updated: 2024/05/07 21:21:58 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_puthex(int nbr, char hex[]);
int	ft_putpointer(void *p);
int	ft_putchar(int c);
int	ft_putnbr(int nb);
int	ft_putstr(char *str);
int	ft_putuint(unsigned int nb);

#endif
