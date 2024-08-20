/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:30:30 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/19 21:13:22 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"
#include "./sources/libft/libft.h"

void	pp_free(char **fly)
{
	int	j;

	j = 0;
	while (fly[j])
		free(fly[j++]);
	free(fly);
}

static inline void	ft_execve_failed(char **shellcmd, char *path)
{
	if (!access(shellcmd[0], F_OK) && !access(shellcmd[0], X_OK))
	{
		if (path)
			free(path);
		if (ft_strchr(shellcmd[0], '/'))
		{
			ft_printf(2, "%s: %s: Is a directory\n", "pipex", shellcmd[0]);
			pp_free(shellcmd);
			exit (126);
		}
		else
		{
			ft_printf(2, "%s: %s: command not found\n", "pipex", shellcmd[0]);
			pp_free(shellcmd);
			exit (127);
		}
	}
	ft_printf(2, "%s: %s: %s\n", "pipex", path, strerror(errno));
	pp_free(shellcmd);
	if (path)
		free(path);
	exit (126);
}

void	exec(char *cmd, char **env)
{
	char	**shellcmd;
	char	*path;

	shellcmd = ft_split(cmd, ' ');
	if (!shellcmd)
		exit(1);
	if (!shellcmd[0] || !cmd[0])
		emptycd(shellcmd, cmd);
	path = findvalidcmd(shellcmd, env);
	if (!path)
	{
		ft_printf(2, "%s: %s: command not found\n", "pipex", shellcmd[0]);
		pp_free(shellcmd);
		exit (127);
	}
	execve(path, shellcmd, env);
	ft_execve_failed(shellcmd, path);
}
