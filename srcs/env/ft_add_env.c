/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:16:33 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:17:48 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_last_list_elem(t_env **ptr)
{
	while(*ptr && (*ptr)->next)
	{
		*ptr = (*ptr)->next;
	}
}

void	ft_modify_env_value(t_env *ptr, char *new_value, int is_equal)
{
	free(ptr->value);
	if (is_equal && !new_value)
		ptr->value = ft_calloc(1, 1);
	else
		ptr->value = new_value;
	//todo check error
}

//void	first_elem(t_env *ptr, char *str)
//{
//	t_env	*new;
//
//	new = NULL;
//	new = ft_new_env(str);
//	ptr->next = new;
//}

void	push_back_env(t_env *ptr, char *str)
{
	t_env *cursor;
	t_env *new;

	cursor = ptr;
	new = NULL;
	ft_last_list_elem(&cursor);
	new = ft_new_env(str);
	//arena pool + ft_perror_exit
	cursor->next = new;
}

void	ft_add_env(char *str, t_shell *sh)
{

	t_env *ptr;
	char *name;
	char *value;

	name = ft_make_env_name(str);
	value = ft_make_env_value(str);
	ptr = ft_env_get_struct(name, sh->env);
	if (!ptr)
	{
		if (sh->env)
			push_back_env(sh->env, str);
		free(value);
	}
	else
		ft_modify_env_value(ptr, value, ft_check_char(str, '='));
	free(name);
}
