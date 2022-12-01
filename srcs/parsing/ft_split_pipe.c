/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:32:16 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/30 14:54:30 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../../includes/minishell.h"
#include <stdio.h>

size_t	ft_nb_string_quote(const char *str, char c)
{
	size_t	i;
	size_t	tot;
	size_t	quote;

	i = 0;
	tot = 0;
	quote = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && !quote)
		{
			while (str[i] && str[i] == c)
				i++;
			if (!str[i])
				return (tot + 1);
			tot++;
		}
		else if (str[i] == '\"' && !quote)
			quote = 1;
		else if (str[i] == '\"' && quote == 1)
			quote = 0;
		if (str[i])
			i++;
	}
	return (tot + 1);
}

size_t	ft_size_str_quote(const char *str, char c, size_t j)
{
	size_t	i;
	size_t quote;

	i = 0;
	quote = 0;
	while (str[j])
	{
		if (str[j] == c && !quote)
			return (i - 1);
		else if (str[j] == '\"' && !quote)
			quote = 1;
		else if (str[j] == '\"' && quote == 1)
			quote = 0;
		i++;
		j++;
	}
	return (i);
}

char	*ft_mallocsplit_quote(char **strs, size_t size, size_t i, t_arena *arena)
{
	strs[i] = ft_alloc(sizeof(**strs) * size, arena);
	// if (!strs[i])
	// {
	// 	while (i >= 0)
	// 	{
	// 		free(strs[i]);
	// 		i--;
	// 	}
	// 	free(strs);
	// 	return (0);
	// }

		return (strs[i]);
}

char	**ft_split_quote(const char *str, char c, t_arena *arena)
{
	char	**strs;
	size_t		size_str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	strs = ft_alloc(sizeof(*strs) * (ft_nb_string_quote(str, c) + 1), arena);
	if (!strs)
		return (0);
	//printf("nb string = %zu", ft_nb_string_quote(str, c));
	while (i < ft_nb_string_quote(str, c))
	{
		while (str[j] && str[j] == c)
			j++;
		size_str = ft_size_str_quote(str, c, j);
		strs[i] = ft_mallocsplit_quote(strs, (size_str + 2), i, arena);
		k = 0;
		while (str[j] && k <=size_str)
			strs[i][k++] = str[j++];
		strs[i++][k] = '\0';
		j++;
	}
	strs[i] = 0;
	return (strs);
}