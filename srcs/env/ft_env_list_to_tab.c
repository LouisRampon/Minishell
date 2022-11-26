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
	char	**tab;
	t_env 	*cursor;

	cursor = sh->env;
	tab = ft_calloc(ft_env_lst_size(sh->env) + 1, sizeof(void *));
	i = 0;
	while (cursor && tab)
	{
		if (cursor->value)
		{
			tab[i] = ft_calloc(ft_strlen(cursor->name) + ft_strlen(cursor->value) + 2, 1);
			if (!tab[i])
				ft_free_tab(tab);
			ft_strcpy(tab[i], cursor->name);
			tab[i][ft_strlen(cursor->name)] = '=';
			ft_strcpy(&tab[i][ft_strlen(cursor->name) + 1], cursor->value);
		}
		else
			tab[i] = ft_strdup(cursor->name);
		if (!tab[i])
			ft_free_tab(tab);
		i++;
		cursor = cursor->next;
	}
	return (tab);
}
