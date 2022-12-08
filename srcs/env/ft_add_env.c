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

void	ft_concat_value(t_env *ptr, char *new_value)
{
	char	*temp;

	temp = ptr->value;
	ptr->value = ft_strjoin(temp, new_value);
	free(new_value);
	free(temp);
}

char 	*ft_remove_plus(char *str, char *name, char *value, t_arena *arena)
{
	char 	*temp;

	temp = ft_strjoin(name, "=");
	str = ft_strjoin_arena(temp, value, arena);
	free(temp);
	return (str);
}


void	ft_add_back(t_shell *sh, char *str, char *value)
{
	if (sh->env)
		push_back_env(sh->env, str);
	free(value);
}

int	ft_init_utils(t_utils *u, char *str)
{
	u->name = NULL;
	u->temp_name = ft_make_env_name(str);
	u->value = ft_make_env_value(str);
	u->index = ft_check_char_index(u->temp_name, '+');
	return (0);
}

void	ft_add_env(char *str, t_shell *sh)
{
	ft_init_utils(&sh->u, str);
	if (sh->u.index != -1)
	{
		sh->u.name = ft_substr(sh->u.temp_name, 0, sh->u.index);
		free(sh->u.temp_name);
		str = ft_remove_plus(str, sh->u.name, sh->u.value, sh->arena);
	}
	else
		sh->u.name = sh->u.temp_name;
	sh->u.ptr = ft_env_get_struct(sh->u.name, sh->env);
	if (!sh->u.ptr)
		ft_add_back(sh, str, sh->u.value);
	else if (sh->u.index != -1)
		ft_concat_value(sh->u.ptr, sh->u.value);
	else
		ft_modify_env_value(sh->u.ptr, sh->u.value);
	free(sh->u.name);
}
