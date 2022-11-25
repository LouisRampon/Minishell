#include "../../includes/minishell.h"

void	ft_close_perror(int fd)
{
	if (close(fd) == -1)
		perror("close");
}

void	ft_dup2_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		perror("dup2");
	ft_close_perror(fd1);
}

int ft_set_fd(t_shell *sh)
{
	if (sh->pipe[0] != 0)
	{
		printf("test 1\n");
		ft_dup2_close(0, sh->pipe[0]);
	}
	if (sh->pipe[1] != 1)
	{
		printf("test 2\n");
		ft_dup2_close(1, sh->pipe[1]);
	}
	if (sh->cmd->fd_in)
	{
		printf("test 3\n");
		ft_dup2_close(0, sh->cmd->fd_in);
	}
	if (sh->cmd->fd_out)
	{
		printf("test 4\n");
		ft_dup2_close(1, sh->cmd->fd_out);
	}
	return (1);
}

int ft_fork(t_shell *sh)
{
	sh->pid = fork();
	if (sh->pid == 0)
	{
		if (ft_check_cmd(sh) == 1)
		{
			ft_set_fd(sh);
			if (is_built_in(sh->cmd) == 1)
				ft_exec_built_in(sh);
			if (execve(sh->cmd->path, sh->cmd->cmd, ft_env_list_to_tab(sh)) == -1)
				ft_perror_exit("minishell: exec failed", 1);
		}
		else
			ft_perror_exit("minishell: commant not found", 1);
	}
	else if (sh->pid > 0)
	{
		if (sh->pipe[0] != 0)
			close(sh->pipe[0]);
		if (sh->pipe[1] != 1)
			close(sh->pipe[1]);
		if (!sh->cmd->next)
			waitpid(sh->pid, NULL, 0);
	}
	return (1);
	// todo else error
}

int	ft_pipe(t_shell *sh)
{
	int temp;

	temp = sh->saved_previous_fd;
	if (sh->cmd->next)
	{
		pipe(sh->pipe);
		sh->saved_previous_fd = sh->pipe[0];
	}
	else
		sh->pipe[1] = 1;
	sh->pipe[0] = temp;
	return (1);
}

int ft_exec_loop(t_shell *sh)
{
	while (sh->cmd)
	{
		ft_pipe(sh);
		if (sh->is_piped == 0 && is_built_in(sh->cmd) == 1)
			ft_exec_built_in(sh);
		else
			ft_fork(sh);
		sh->cmd = sh->cmd->next;
	}
	return (0);
}
