/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:01 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:19:02 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_make_env_value(char *str)
{
	char *value;
	char **temp;

	value = NULL;
	temp = ft_split(str, '=');
	if (temp)
	{
		free(temp[0]);
		if (temp[1] != 0)
			free(temp[2]);
		value = temp[1];
		free(temp);
	}
	else
		ft_perror_exit("Malloc error", 1);
	return (value);
}

char	*ft_make_env_name(char *str)
{
	char *name;
	char **temp;

	name = NULL;
	temp = ft_split(str, '=');
	if (temp)
	{
		if (temp[1] != 0)
			free(temp[2]);
		free(temp[1]);
		name = temp[0];
		free(temp);
	}
	else
		ft_perror_exit("Malloc error", 1);
	return (name);
}

char	*ft_env_get_name(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (env->name);
		env = env->next;
	}
	return (NULL);
}

char	*ft_env_get(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*ft_env_get_struct(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
