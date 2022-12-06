/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:52:50 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/06 17:13:35 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sig_ignit_heredoc(int nothing)
{
	if (nothing == SIGINT)
	{
		printf("\n");
		exit(1);
	}
}

void	ft_child_heredoc(char *delimiter, int fd_pipe[2])
{
	char	*str;

	signal(SIGINT, ft_sig_ignit_heredoc);
	close(fd_pipe[0]);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			exit(0);
		}
		if (!ft_strcmp(str, delimiter))
		{
			close(fd_pipe[1]);
			free(str);
			exit(0);
		}
		ft_putstr_fd(str, fd_pipe[1]);
		ft_putstr_fd("\n", fd_pipe[1]);
		free(str);
	}
}

int	ft_parent_heredoc(int fd_pipe[2], int pid)
{
	int	status;

	close(fd_pipe[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, ft_sig_ignit_heredoc);
	return (fd_pipe[0]);
}

int	ft_heredoc(char *delimiter, t_shell *shell)
{
	int	fd_pipe[2];
	int	pid;

	(void)shell;
	if (!delimiter || ft_strlen(delimiter) == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	if (pipe(fd_pipe) == -1)
	{
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error heredoc");
		return (-1);
	}
	if (pid == 0)
		ft_child_heredoc(delimiter, fd_pipe);
	else
		return (ft_parent_heredoc(fd_pipe, pid));
	
	return (0);
}
