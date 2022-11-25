/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:35 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:15:37 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_saved_pwd(t_shell *sh, char *str)
{
	free(sh->saved_pwd);
	sh->saved_pwd = ft_strdup(str);
}

void	ft_pwd(t_shell *sh)
{
	printf("%s\n", sh->saved_pwd);
}
