/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:08 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:15:09 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *sh)
{
	ft_free_env_list(sh->env, ft_env_lst_size(sh->env));
	ft_free_arena(&sh->arena);
	exit(1);
}
