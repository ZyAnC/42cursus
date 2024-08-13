/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:02:49 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/04 17:52:46 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*getnewline(char *storage);
char	*g_ft_strjoin(char *s1, char *s2);
char	*g_ft_strchr( char *s, int c);
char	*ft_getline(char *src);
size_t	g_ft_strlen(const char *str);
char	*ft_free(char **str);

#endif
