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
	char	*value;

	value = ft_strchr(str, '=');
	if (value)
		value = ft_strdup(++value);
	return (value);
}

char	*ft_make_env_name(char *str)
{
	char	*name;
	int		index;

	name = NULL;
	index = ft_check_char_index(str, '=');
	if (index)
		name = ft_substr(str, 0, index);
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
