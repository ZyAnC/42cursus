/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:28:09 by yzheng            #+#    #+#             */
/*   Updated: 2024/08/19 21:19:37 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./sources/libft/libft.h"
#include "pipex.h"

char	*findpath(char **shellcmd, char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	if (!env[i])
	{
		ft_printf(
			2, "%s: %s: No such file or directory\n", "pipex", shellcmd[0]);
		pp_free(shellcmd);
		exit (127);
	}
	return (env[i]);
}

static inline char	*check_filename(char **filename, char **cmd)
{
	char	*path;
	char	*full_path;
	int		i;

	i = 0;
	while (filename[i])
	{
		path = ft_strjoin(filename[i++], "/");
		if (!path)
			return (0);
		full_path = ft_strjoin(path, cmd[0]);
		free(path);
		if (!full_path)
			return (0);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			pp_free(filename);
			return (full_path);
		}
		free(full_path);
	}
	pp_free(filename);
	return (0);
}

static inline char	*pathincmd(char **shellcmd)
{
	if (!access(shellcmd[0], F_OK))
		return (ft_strdup(shellcmd[0]));
	else
	{
		ft_printf(
			2, "%s: %s: No such file or directory\n", "pipex", shellcmd[0]);
		pp_free(shellcmd);
		exit (127);
	}
}

char	*findvalidcmd(char **shellcmd, char **env)
{
	char	*path;
	char	**filename;

	if (ft_strchr(shellcmd[0], '/'))
		return (pathincmd(shellcmd));
	path = findpath(shellcmd, env);
	filename = ft_split(path + 5, ':');
	if (!filename)
		return (0);
	return (check_filename(filename, shellcmd));
}

void	emptycd(char **shellcmd, char *cmd)
{
	pp_free(shellcmd);
	if (cmd[0] == ' ' || !cmd[0])
		ft_printf(2, "%s: %s: command not found\n", "pipex", cmd);
	else
		ft_printf(2, "%s: permission denied:\n", "pipex");
	exit (127);
}
