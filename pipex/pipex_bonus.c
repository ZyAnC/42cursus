
#include "pipex.h"
#include "./sources/libft/libft.h"
#include "./sources/libft/get_next_line.h"

static void	child(int i,char *filename, char *cmd, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	int		fd;
	printf("%d",i);
	if (pipe(p_fd) == -1)
		main_exit(NULL, 8);
		
	pid = fork();


	if (pid == -1)
		main_exit(NULL, 9);
	
		
	if (pid == 0)
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
			{
		
				child(i,av[1], av[i], env);
				i++;
			}
	}
	else if( i == 3)
	{
		while (i < ac - 2)
			child2(av[i++], env);
	}
	if (i == ac - 2)

	{
		int		p_fd[2];
		pid_t	pid;
		int outfd;
		if (pipe(p_fd) == -1)
			main_exit(NULL, 8);
		pid = fork();
		if (pid == -1)
			main_exit(NULL, 9);
		if (!pid)
		{
			outfd = open_file(av[ac -1], 1);
			dup2(outfd, 1);
			dup2(p_fd[0], 0);
			close(outfd);
			close(p_fd[1]);
			close(p_fd[0]);
			exec(av[ac -2], env);
		}
	
	}
}

int	main(int ac, char **av, char **env)
{
	int	fd_out;
	pid_t pid;
	pid_t pid2;
	if (ac < 5)
		main_exit(NULL, 0);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac < 6)
			main_exit(NULL, 1);
		fd_out = open_file(av[ac - 1], 2);
		childdoc(av);
		choose_modle(3, ac, av, env);
		
	}
	else
	{	pid = fork();
		printf("pid:%d\n",pid);
		pid2 = fork();
	
		choose_modle(2, ac, av, env);
	}
}