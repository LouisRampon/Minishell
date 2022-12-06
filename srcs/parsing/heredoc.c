/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:52:50 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/05 15:16:14 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_child_heredoc(char *delimiter, int fd_pipe[2])
{
	char	*str;

	close(fd_pipe[0]);
	while (1)
	{
		str = readline("> ");
		if (!ft_strcmp(str, delimiter))
		{
			close(fd_pipe[1]);
			exit(0);
		}
		ft_putstr_fd(str, fd_pipe[1]);
		ft_putstr_fd("\n", fd_pipe[1]);
	}
}

int	ft_parent_heredoc(int fd_pipe[2], int pid)
{
	int	status;

	close(fd_pipe[1]);
	waitpid(pid, &status, 0);
	return (fd_pipe[0]);
}

int	ft_heredoc(char *delimiter)
{
	int	fd_pipe[2];
	int	pid;

	if (pipe(fd_pipe) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		printf("fork failed\n");
		return (-1);
	}
	if (pid == 0)
		ft_child_heredoc(delimiter, fd_pipe);
	else
		return (ft_parent_heredoc(fd_pipe, pid));
	return (0);
}
