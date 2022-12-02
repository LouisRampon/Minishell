/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:52:50 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/02 15:18:09 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_heredoc(char *delimiter)
{
	int fd_pipe[2];
	int pid;
	char *str;
	int status;

	status = 0;
	if (pipe(fd_pipe) == -1)
		return (-1);
	if ((pid = fork()) < 0)
    {
       printf("fork failed\n");
       return (-1);
    }
	if (pid == 0)
	{
		//ft_child_heredoc()
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
	else
	{
		close(fd_pipe[1]);
		waitpid(pid, &status, 0);
		return(fd_pipe[0]);
		//ft_parent_heredoc();
	}
	
}  