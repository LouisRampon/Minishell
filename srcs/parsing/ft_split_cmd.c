/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:32:16 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/30 14:51:26 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"
#include <stdio.h>

char *remoce_char(char *str, size_t pos)
{
	size_t len;

	len = ft_strlen(str);
	while (pos < len)
	{
		str[pos] = str[pos + 1];
		pos++;
	}
	return (str);
}

size_t	ft_nb_string_cmd(const char *str, char c)
{
	size_t	i;
	size_t	tot;
	bool single_quote;
	bool double_quote;
	
	single_quote = 0;
	double_quote = 0;
	i = 0;
	tot = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;		
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (str[i] == c && !single_quote && !double_quote)
		{
			while (str[i] && str[i] == c)
				i++;
			if (!str[i])
				return (tot + 1);
			tot++;
		}
		if (str[i])
			i++;
	}
	return (tot + 1);
}

size_t	ft_size_str_cmd(char *str, char c, size_t j)
{
	size_t	i;
	bool single_quote;
	bool double_quote;
	
	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[j])
	{
		if (str[j] == '"' && !single_quote)
		{
			str = remoce_char(str, j);
			double_quote = !double_quote;
		}	
		if (str[j] == '\'' && !double_quote)
		{
			str = remoce_char(str, j);
			single_quote = !single_quote;
		}
		if (str[j] == c && !single_quote && !double_quote)
			return (i - 1);
		i++;
		j++;
	}
	return (i);
}

char	*ft_mallocsplit_cmd(char **strs, size_t size, size_t i, t_arena *arena)
{
	strs[i] = ft_alloc(sizeof(**strs) * size, arena);
	// if (!strs[i])
	// 	return (0);
	// else
		return (strs[i]);
}

char	**ft_split_cmd(char *str, char c, t_arena *arena)
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
	strs = ft_alloc(sizeof(*strs) * (ft_nb_string_cmd(str, c) + 1), arena);
	if (!strs)
		return (0);
	//printf("nb string = %zu", ft_nb_string_quote(str, c));
	while (i < ft_nb_string_cmd(str, c))
	{
		while (str[j] && str[j] == c)
			j++;
		size_str = ft_size_str_cmd(str, c, j);
		strs[i] = ft_mallocsplit_cmd(strs, (size_str + 2), i, arena);
		k = 0;
		while (str[j] && k <=size_str)
			strs[i][k++] = str[j++];
		strs[i++][k] = '\0';
		j++;
	}
	strs[i] = 0;
	return (strs);
}
