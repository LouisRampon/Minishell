/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:16:22 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:16:23 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec(t_shell *sh)
{
	char	**tab;

	tab = ft_env_list_to_tab(sh);
	ft_check_cmd(sh);
	ft_set_fd(sh);
	if (is_built_in(sh->cmd) == 1)
	{
		ft_exec_built_in(sh);
		exit(0);
	}
	if (execve(sh->cmd->path, sh->cmd->cmd, tab) == -1)
	{
		ft_free_tab(tab);
		if (!ft_strchr(sh->cmd->cmd[0], '/') || !sh->cmd->cmd[0])
			ft_perror_exit(sh->cmd->cmd[0], "", "command not found", 127);
		else
			ft_perror_exit(sh->cmd->cmd[0], "", \
			"No such file or directory", 126);
	}
	return (1);
}

void	ft_wait_child(t_shell *sh)
{
	int	sig;

	if (sh->pipe[0] != 0)
		close(sh->pipe[0]);
	if (sh->pipe[1] != 1)
		close(sh->pipe[1]);
	if (!sh->cmd->next)
	{
		waitpid(sh->pid, &sh->pid, 0);
		g_return_value = WEXITSTATUS(sh->pid);
		sig = ft_signal_handle(sh->pid);
		while (waitpid(-1, &sh->pid, 0) != -1)
			if (!sig)
				sig = ft_signal_handle(sh->pid);
	}
}

int	ft_fork(t_shell *sh)
{
	ft_unset_term(sh);
	signal(SIGINT, &ft_signal_reset);
	signal(SIGQUIT, &ft_signal_reset);
	sh->pid = fork();
	if (sh->pid == -1)
	{
		perror("minishell: fork");
		exit(1);
	}
	if (sh->pid == 0)
		ft_exec(sh);
	else if (sh->pid > 0)
		ft_wait_child(sh);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	return (1);
	// todo else error
}

int	ft_pipe(t_shell *sh)
{
	int	temp;

	temp = sh->saved_previous_fd;
	if (sh->cmd->next)
	{
		pipe(sh->pipe);
		sh->saved_previous_fd = sh->pipe[0];
		sh->is_piped = 1;
	}
	else
		sh->pipe[1] = 1;
	sh->pipe[0] = temp;
	return (1);
}

int	ft_exec_loop(t_shell *sh)
{
	while (sh->cmd)
	{
		ft_pipe(sh);
		if (sh->is_piped == 0 && is_built_in(sh->cmd) == 1)
		{
			ft_set_fd(sh);
			ft_exec_built_in(sh);
			ft_fd_reset(sh);
		}
		else
			ft_fork(sh);
		if (sh->cmd->fd_in != 0)
			close(sh->cmd->fd_in);
		if (sh->cmd->fd_out != 1)
			close(sh->cmd->fd_out);
		sh->cmd = sh->cmd->next;
	}
	return (0);
}
