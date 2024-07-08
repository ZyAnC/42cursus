/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzheng <yzheng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 08:17:24 by yzheng            #+#    #+#             */
/*   Updated: 2024/07/04 21:59:44 by yzheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"
int	open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}
typedef struct ppst
{
    int pipefd[2];
    pid_t pid ;
}ppt;
void errorexit(const char *mess)
{
    perror(mess);
    exit(EXIT_FAILURE);
}

void pp_free(char **fly)
{
    int   j;

    j = 0;
    while (fly[j])
        free(fly[j++]);
    free(fly);
}
char *findpath(char **shellcmd, char **env)
{
    int i;
   
    i = 0;
    while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
    if(!env[i])
    {
        pp_free(shellcmd);
        errorexit("can't find environment path");
    }
    return(env[i]);
}


char *check_filename(char **filename, char **cmd)
{
    char *path;
    char *full_path;
    int   i;
    
    i = 0;
    while(filename[i])
    {
        path = ft_strjoin(filename[i++],"/");
        if(!path)
            return (0);
        full_path = ft_strjoin(path,cmd[0]);
        free(path);
        if(!full_path)
            return (0);
        if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
        {
            pp_free(filename);
            return (full_path);
        }
        free(full_path);
    }
    pp_free(filename); 
    errorexit("command not found");
    return (0);
}

char *findvalidcmd(char **shellcmd, char **env)
{
    char *path;
    char **filename;
   
    path = findpath(shellcmd, env);
    filename = ft_split(path + 5, ':');
	if (!filename)
		return (0);
    return(check_filename(filename,shellcmd));
}
static inline void exec(char *cmd, char **env)
{
    char **shellcmd;
    char *path;
    
    shellcmd = ft_split(cmd,' ');
    path = findvalidcmd(shellcmd, env);
     printf("%s",path);
    int i = 0;
    while(shellcmd[i])
        printf("%s",shellcmd[i++]);
// execve(path, shellcmd, env);
   // errorexit("execve");
}
void	child(char **av, int *p_fd, char **env)
{
	int		fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exec(av[2], env);
}

void	parents(char **av, int *p_fd, char **env)
{
    
	int		fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exec(av[3], env);
}

int main(int ac, char **av, char **env)
{
   
  
    
   
    int		p_fd[2];
	pid_t	pid;
    if (ac != 5)
    {
        fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", av[0]);
        exit(EXIT_FAILURE);
    }
	
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child(av, p_fd, env);
	parents(av, p_fd, env);
}