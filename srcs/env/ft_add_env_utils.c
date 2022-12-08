/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:17:03 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/08 11:17:06 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_last_list_elem(t_env **ptr)
{
	while (*ptr && (*ptr)->next)
	{
		*ptr = (*ptr)->next;
	}
}

void	ft_modify_env_value(t_env *ptr, char *new_value)
{
	if (!new_value)
		return ;
	free(ptr->value);
	ptr->value = new_value;
}

void	push_back_env(t_env *ptr, char *str)
{
	t_env	*cursor;
	t_env	*new;

	cursor = ptr;
	new = NULL;
	ft_last_list_elem(&cursor);
	new = ft_new_env(str);
	if (!new)
	{
		ft_putstr_fd("Failed to add a node to env list\n", 2);
		return ;
	}
	cursor->next = new;
}
