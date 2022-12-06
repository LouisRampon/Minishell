/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:47:20 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/06 14:47:22 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_close_perror(int fd)
{
	if (close(fd) == -1)
		perror("close");
}

static void	ft_dup2_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		perror("dup2");
	ft_close_perror(fd1);
}

void	ft_fd_reset(t_shell *sh)
{
	ft_dup2_close(sh->dup_std_fd[0], 0);
	sh->dup_std_fd[0] = dup(0);
	ft_dup2_close(sh->dup_std_fd[1], 1);
	sh->dup_std_fd[1] = dup(1);
}

int	ft_set_fd(t_shell *sh)
{
	if (sh->pipe[0] != 0)
		ft_dup2_close(sh->pipe[0], 0);
	if (sh->pipe[1] != 1)
		ft_dup2_close(sh->pipe[1], 1);
	if (sh->cmd->fd_in)
		ft_dup2_close(sh->cmd->fd_in, 0);
	if (sh->cmd->fd_out != 1)
		ft_dup2_close(sh->cmd->fd_out, 1);
	if (sh->saved_previous_fd)
		close(sh->saved_previous_fd);
	return (1);
}
