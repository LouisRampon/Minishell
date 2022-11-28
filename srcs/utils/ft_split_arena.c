/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:18:45 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/28 15:18:47 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_nb_string(const char *str, char c)
{
	size_t	i;
	size_t	tot;

	i = 0;
	tot = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			tot++;
		while (str[i] != c && str[i])
			i++;
	}
	return (tot);
}

static size_t	ft_size_str(const char *str, char c, size_t j)
{
	size_t	i;

	i = 0;
	while (str[j])
	{
		if (str[j] == c)
			return (i);
		i++;
		j++;
	}
	return (i);
}

static char	*ft_mallocsplit(char **strs, size_t size, size_t i, t_arena *arena)
{
	strs[i] = ft_alloc(sizeof(**strs) * size, arena);
	if (!strs[i])
	{
		while (i >= 0)
		{
			free(strs[i]);
			i--;
		}
		free(strs);
		return (0);
	}
	else
		return (strs[i]);
}

char	**ft_split_arena(const char *str, char c, t_arena *arena)
{
	char	**strs;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	strs = ft_alloc(sizeof(*strs) * (ft_nb_string(str, c) + 1), arena);
	if (!strs)
		return (0);
	while (i < ft_nb_string(str, c))
	{
		while (str[j] == c && str[j])
			j++;
		strs[i] = ft_mallocsplit(strs, (ft_size_str(str, c, j) + 1), i, arena);
		k = 0;
		while (ft_size_str(str, c, j) && str[j])
			strs[i][k++] = str[j++];
		strs[i++][k] = '\0';
	}
	strs[i] = 0;
	return (strs);
}
