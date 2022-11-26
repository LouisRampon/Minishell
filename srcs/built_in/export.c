/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:16 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:15:17 by jereverd         ###   ########lyon.fr   */
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

	//bite
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
			if (cursor->name)
				printf("declare -x %s=\"%s\"\n", cursor->name, cursor->value);
			cursor = cursor->next;
		}
	}
}

int ft_check_equal(char *str, char equal)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == equal)
			return (1);
		i++;
	}
	return (0);
}

int ft_only_equal(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '=')
			count++;
		i++;
	}
	//printf("count = %zu\n strlen == %zu\n", count, ft_strlen(str));
	if (ft_strlen(str) == count)
		return (1);
	return (0);
}

int ft_check_valid_indentifier(char *str)
{
	int		i;
	size_t	count;
	//char	*index_equal;

	i = 0;
	count = 0;
//	index_equal = ft_strchr(str);
	if (ft_only_equal(str) == 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_' || str[i] == '=')
			count++;
		i++;
	}
	if (count == ft_strlen(str))
		return (1);
	return (0);
}


int ft_parse_export_arg(char **tab)
{
	int 	i;
	char	*index_equal;

	i = 1;

	while (tab[i])
	{
		index_equal = ft_strchr(tab[i], '=');
		if (ft_check_valid_indentifier(tab[i]) == 1)
		{
//			if (index_equal)
//			{
//				index_equal--;
//				if (ft_isalnum(*index_equal) == 1 || *index_equal == '_')
//			}
			return (1);
		}
		else
			printf("bad identifier\n");
		i++;
	}
	return (0);
}

void	ft_export(t_shell *sh, char *cmd)
{
	t_command *ptr;
	(void) cmd;
	if (!sh->cmd->cmd[1])
	{
		ft_print_export(sh);
		return;
	}

	ptr = sh->cmd;
	while (ptr)
	{
		if (ft_parse_export_arg(ptr->cmd) == 1)
			ft_add_env(cmd, sh);
		ptr = ptr->next;
	}
}


//		//m'occuper du cas ou il n'y a pas de =
//		if (ft_strchr(cmd, '='))
//		{
//			if (ft_check_valid_identifier(cmd) == 1)
//				ft_add_env(cmd, sh);
//		}
//		else
//			push_back_env(sh->env, cmd); //fix elem vide
