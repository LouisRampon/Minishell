/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:43:49 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/28 13:43:50 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	swap_elem(t_env *elem1, t_env *elem2)
{
	char		*value;
	char		*name;

	value = elem1->value;
	name = elem1->name;
	elem1->value = elem2->value;
	elem1->name = elem2->name;
	elem2->value = value;
	elem2->name = name;
}

void	ft_sort_env_list(t_env *sorted)
{
	t_env	*ptr;

	while (sorted->next)
	{
		ptr = sorted->next;
		while (ptr)
		{
			if (ft_strcmp(sorted->name, ptr->name) > 0)
				swap_elem(sorted, ptr);
			ptr = ptr->next;
		}
		sorted = sorted->next;
	}
}

t_env	*copy_elem(t_env *lst)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->next = 0;
	new->value = lst->value;
	new->name = lst->name;
	return (new);
}

t_env	*ft_cpy_env_list(t_env *lst)
{
	t_env	*sorted;
	t_env	*ptr;

	if (!lst->next)
		return (lst);
	sorted = copy_elem(lst);
	ptr = sorted;
	while (lst->next)
	{
		ptr->next = copy_elem(lst->next);
		ptr = ptr->next;
		lst = lst->next;
	}
	ft_sort_env_list(sorted);
	return (sorted);
}

void	ft_print_export(t_shell *sh)
{
	t_env	*cpy;
	t_env	*cursor;

	cpy = ft_cpy_env_list(sh->env);
	// todo error
	ft_sort_env_list(cpy);
	cursor = cpy;
	if (cpy)
	{
		while (cursor)
		{
			if (cursor->value)
				printf("declare -x %s=\"%s\"\n", cursor->name, cursor->value);
			else
				printf("declare -x %s\n", cursor->name);
			cursor = cursor->next;
		}
	}
}
