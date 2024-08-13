/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:17:24 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/12 16:31:38 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"
#include "./sources/libft/libft.h"
typedef struct s_pipex
{
	int		p_fd[2];
	int		infd;
	int		outfd;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

void	close_exit(int model, t_pipex *px)
{
	if (model == 0)
		ft_printf(2, "usage: in_file cmd1 cmd2 out_file\n");
	else if (model == 1)
		ft_printf(2, "Pipe failed\n");
	else if (model == 2)
		ft_printf(2, "Fork failed\n");

	if (px->p_fd[0] != -1)
		close(px->p_fd[0]);
	if (px->p_fd[1] != -1)
		close(px->p_fd[1]);
	if (px->infd != -1)
		close(px->infd);
	if (px->outfd != -1)
		close(px->outfd);
	printf("%d",px->p_fd[0]);
	printf("%d",px->p_fd[1]);
	if(model != 4)
		exit(1);
}	
int	op_file(char *filename, int mode,t_pipex *px)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
		
			ft_printf(2, "%s: %s: %s\n", "pipex", filename, strerror(errno));
			exit(1);
		}
	}
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd == -1)
		{
			close(px->infd);
			close(px->p_fd[0]);
			close(px->p_fd[1]);
			ft_printf(2, "%s: %s: %s\n", "pipex", filename, strerror(errno));
			exit(1);
		}
	}
	return (fd);
}
int	close_all(t_pipex *px)
{
	int status1;
	int status2;
	int exit_code;
	
	if (px->p_fd[0] != -1)
		close(px->p_fd[0]);
	if (px->p_fd[1] != -1)
		close(px->p_fd[1]);
	if (px->infd != -1)
		close(px->infd);
	if (px->outfd != -1)
		close(px->outfd);

	waitpid(px->pid1, &status1, 0);
	waitpid(px->pid2, &status2, 0);
	if ((status1 & 0xFF) == 0)
		exit_code = (status1 >> 8) & 0xFF;
	else
		exit_code = 1; 
	if ((status2 & 0xFF) == 0)
		exit_code = (status2 >> 8) & 0xFF;
	else
		exit_code = 1;

	return(exit_code);
}

void	child(int model, char **av, t_pipex *px, char **env)
{
	
	if (model == 0)
	{
		
		px->infd = op_file(av[1], 0,px);
		dup2(px->infd, 0);
		dup2(px->p_fd[1], 1);
		close(px->infd);
		close(px->p_fd[0]);
		close(px->p_fd[1]);
		exec(av[2], env);
	}
	else
	{
	
		px->outfd = op_file(av[4], 1,px);
		dup2(px->outfd, 1);
		dup2(px->p_fd[0], 0);
		close(px->outfd);
		close(px->p_fd[1]);
		close(px->p_fd[0]);
		exec(av[3], env);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	px;
	px.p_fd[0] = -1;
    px.p_fd[1] = -1;
	px.infd = -1;
	px.outfd = -1;
	

	if (ac != 5)
		close_exit(0,&px);
	if (pipe(px.p_fd) == -1)
		close_exit(1,&px);	
	px.pid1 = fork();


	if (px.pid1 == -1)
		close_exit(2,&px);
	if (px.pid1 == 0)
		child(0, av, &px, env);
	px.pid2 = fork();
	if (px.pid2 == -1)
		close_exit(2,&px);
	if (px.pid2 == 0)
		child(1, av, &px, env);
	return (close_all(&px));
}

