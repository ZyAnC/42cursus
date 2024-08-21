/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:10:36 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/21 15:36:07 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./sources/libft/libft.h"
#include "./sources/libft/get_next_line.h"

static void	child(char *filename, char *cmd, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	int		fd;

	if (pipe(p_fd) == -1)
		main_exit(NULL, 8);
	pid = fork();
	if (pid == -1)
		main_exit(NULL, 9);
	if (!pid)
	{
		fd = open_file(filename, 0);
		dup2(fd, 0);
		dup2(p_fd[1], 1);
		close(p_fd[0]);
		exec(cmd, env);
	}
	else
	{
		dup2(p_fd[0], 0);
		close(p_fd[1]);
		waitpid(pid, NULL, 0);
	}
}

static inline void	childdoc(char **av)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
	{
		ft_printf(2, "Pipe failed");
		exit (1);
	}
	pid = fork();
	if (pid == -1)
	{	
		ft_printf(2, "Fork failed");
		exit (1);
	}
	if (!pid)
		getdoc(av, p_fd);
	else
	{
		dup2(p_fd[0], 0);
		close(p_fd[1]);
		waitpid(pid, NULL, 0);
	}
}

static void	child2(char *cmd, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		main_exit(NULL, 8);
	pid = fork();
	if (pid == -1)
		main_exit(NULL, 9);
	if (!pid)
	{
		dup2(p_fd[1], 1);
		close(p_fd[0]);
		exec(cmd, env);
	}
	else
	{
		dup2(p_fd[0], 0);
		close(p_fd[1]);
		waitpid(pid, NULL, 0);
	}
}

void	choose_modle(int i, int ac, char **av, char **env)
{
	if (i == 2)
	{
		while (i < ac - 2)
			child(av[1], av[i++], env);
	}
	else
	{
		while (i < ac - 2)
			child2(av[i++], env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	fd_out;

	if (ac < 5)
		main_exit(NULL, 0);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			main_exit(NULL, 1);
		fd_out = open_file(av[ac - 1], 2);
		childdoc(av);
		choose_modle(3, ac, av, env);
		dup2(fd_out, 1);
		close(fd_out);
		exec(av[ac - 2], env);
	}
	else
	{
		fd_out = open_file(av[ac - 1], 1);
		choose_modle(2, ac, av, env);
		dup2(fd_out, 1);
		close(fd_out);
		exec(av[ac - 2], env);
	}
}
