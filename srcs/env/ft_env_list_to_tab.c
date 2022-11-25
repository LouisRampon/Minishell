/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list_to_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:07 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:19:08 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_env_list_to_tab(t_shell *sh)
{
	int 	i;
	int 	var_count;
	int 	name_lenght;
	int 	value_lenght;
	char	**tab;
	t_env 	*cursor;

	cursor = sh->env;
	var_count = ft_env_lst_size(sh->env);
	tab = ft_calloc(var_count + 1, sizeof (*tab));
	if (!tab)
		return (NULL);
	i = 0;
	while (cursor)
	{
		name_lenght = ft_strlen(cursor->name);
		value_lenght = ft_strlen(cursor->value);
		tab[i] = malloc(sizeof (char) * (name_lenght + value_lenght + 2));
		if(!tab[i])
		{
			ft_free_tab(tab);
			ft_perror_exit("Malloc failure", 1);
		}
		ft_strcpy(tab[i], cursor->name);
		tab[i][name_lenght] = '=';
		ft_strcpy(&tab[i][name_lenght + 1], cursor->value);
		i++;
		cursor = cursor->next;
	}
	return (tab);
}
