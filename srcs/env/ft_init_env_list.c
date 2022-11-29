/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:22 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:19:23 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_new_env(char *str)
{
	t_env *env;
	char **temp;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->next = NULL;
	temp = ft_split(str, '=');
	env->name = temp[0];
	if (ft_check_char(str, '=') && !temp[1])
		env->value = ft_calloc(1,1);
	else
		env->value = temp[1];
	free(temp);
	return (env);
	//todo free and check error
}

int	ft_env_lst_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	ft_free_env_list(t_env *env, int size)
{
	t_env *tmp;
	int i;

	i = 0;
	while (i < size)
	{
		tmp = env->next;
		free(env->value);
		free(env->name);
		free(env);
		env = NULL;
		env = tmp;
		i++;
	}
}

void	ft_create_env_list(t_shell *sh, char **envp)
{
	int		i;
	t_env	*previous;
	t_env	*new;

	previous = NULL;
	new = NULL;
	i = 0;
	while (envp[i])
	{
		new = ft_new_env(envp[i]);
		if (!new)
		{
			//fix free_env_list
			ft_free_env_list(sh->env, ft_env_lst_size(sh->env));
			ft_putstr_fd("malloc failure", 2);
		}
		if (previous)
			previous->next = new;
		else
			sh->env = new;
		previous = new;
		i++;
	}
}
