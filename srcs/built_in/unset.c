/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:39 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:15:40 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_shell *sh)
{
	int	i;

	i = 1;
	if (!sh->env)
		return ;
	g_return_value = 0;
	while (sh->cmd->cmd[i])
	{
		if (ft_parse_export_arg(sh->cmd->cmd[i], sh->arena, 2) == 1)
			ft_del_env(sh->cmd->cmd[i], sh);
		else
			ft_perror("unset: ", sh->cmd->cmd[i], "not a valid identifier", 1);
		i++;
	}
}
