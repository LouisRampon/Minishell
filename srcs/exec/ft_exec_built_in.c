/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:16:17 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:16:19 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_exec_built_in(t_shell *sh)
{
	if (ft_strcmp(sh->cmd->cmd[0], "echo") == 0)
		ft_echo(sh->cmd->cmd);
	else if (ft_strcmp(sh->cmd->cmd[0], "unset") == 0)
		ft_unset(sh);
	else if (ft_strcmp(sh->cmd->cmd[0], "cd") == 0)
		ft_cd(sh);
	else if (ft_strcmp(sh->cmd->cmd[0], "export") == 0)
		ft_export(sh);
	else if (ft_strcmp(sh->cmd->cmd[0], "pwd") == 0)
		ft_pwd(sh);
	else if (ft_strcmp(sh->cmd->cmd[0], "env") == 0)
		ft_env(sh);
	else if (ft_strcmp(sh->cmd->cmd[0], "exit") == 0)
		ft_exit();
}
