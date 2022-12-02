/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:14:59 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:15:00 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_shell *sh)
{
	t_env	*ptr;

	if (sh->env)
	{
		ptr = sh->env;
		while (ptr)
		{
			if (ptr->name && ptr->value)
				printf("%s=%s\n", ptr->name, ptr->value);
			ptr = ptr->next;
		}
	}
}
