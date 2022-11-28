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
	int i;

	i = 1;
	while (sh->cmd->cmd[i])
	{
		if (ft_parse_export_arg(sh->cmd->cmd) == 1)
			ft_del_env(sh->cmd->cmd[i], sh);
		i++;
	}
}
