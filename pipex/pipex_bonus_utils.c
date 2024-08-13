/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:33:00 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/12 16:14:22 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./sources/libft/libft.h"
#include "./sources/libft/get_next_line.h"

void	main_exit(char *filename, int i)
{
	if (!i)
	{
		ft_printf(2, "usage:\nin_file1 shellcmd_1 shellcmd_2 out_file\n");
		exit (1);
	}
	else if (i == 8)
	{
		ft_printf(2, "Pipe failed");
		exit (1);
	}
	else if (i == 9)
	{
		ft_printf(2, "Fork failed");
		exit (1);
	}
	if (i == 2)
	{
		ft_printf(2, "%s: %s: %s\n", "pipex", filename, strerror(errno));
		exit (1);
	}
	ft_printf(2, "usage:\n here_doc LIMITER shellcmd_1 shellcmd_2 out_file\n");
	exit (1);
}

int	open_file(char *filename, int i)
{
	int	fd;

	if (i == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			main_exit(filename, 2);
	}
	else if (i == 1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd == -1)
			main_exit(filename, 2);
	}
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			main_exit(filename, 2);
	}
	return (fd);
}

void	getdoc(char **av, int p_fd[2])
{
	char	*doc_in;

	close(p_fd[0]);
	while (1)
	{
		doc_in = get_next_line(0);
		if (ft_strncmp(doc_in, av[2], ft_strlen(av[2])) == 0)
		{
			free(doc_in);
			exit(0);
		}
		ft_putstr_fd(doc_in, p_fd[1]);
		free(doc_in);
	}
}
