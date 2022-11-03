/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/03 16:34:29 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_env(char **env, t_list **env_list)
{
	int	i;

	i = 0;
	(void)env_list;
	(void)env;
	// while(env[i])
	// {
	// 	ft_lstadd_back(env_list, ft_lstnew(env[i]));

	// 	i++;
	// }
	return(0);
}

int	ft_parsing(char *str, char **env)
{
	t_list **env_list;
	
	(void)str;
	env_list = malloc(sizeof(t_list));
	 if (!env_list)
	 	return (1);
	if (ft_create_env(env, env_list))
		return (1);
	return (0);
}
