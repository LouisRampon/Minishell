/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:18:54 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:18:57 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_del_list_elem(t_env *ptr)
{
	free(ptr->value);
	free(ptr->name);
	free(ptr);
}

void	ft_del_env(char *str, t_shell *sh)
{
	t_env	*ptr;
	t_env 	*ptr_prev;
	char	*name;

	name = ft_env_get_name(str, sh->env);
	ptr = sh->env;
	if (name == ptr->name)
	{
		ptr_prev = ptr->next;
		ft_del_list_elem(ptr);
		sh->env = ptr_prev;
		return ;
	}
	ptr_prev = NULL;
	while (ptr)
	{
		if (name == ptr->name)
		{
			ptr_prev->next = ptr->next;
			ft_del_list_elem(ptr);
			break ;
		}
		ptr_prev = ptr;
		ptr = ptr->next;
	}
}
