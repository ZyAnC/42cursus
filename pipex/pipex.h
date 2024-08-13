/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:11:07 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/12 15:58:03 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

char	*findvalidcmd(char **shellcmd, char **env);
void	exec(char *cmd, char **env);
void	pp_free(char **fly);
void	emptycd(char **shellcmd, char *cmd);

void	getdoc(char **av, int p_fd[2]);
void	main_exit(char *filename, int i);
int	open_file(char *filename, int i);
#endif