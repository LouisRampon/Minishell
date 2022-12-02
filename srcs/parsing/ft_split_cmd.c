/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:32:16 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/02 13:21:19 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"
#include <stdio.h>

char *remoce_char(char *str, size_t pos)
{
	while (str[pos + 1])
	{
		str[pos] = str[pos + 1];
		pos++;
	}
	str[pos] = '\0';
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
	tot = 1;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;		
		else if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (str[i] == c && !single_quote && !double_quote)
		{
			while (str[i] && str[i] == c)
				i++;
			if (!str[i])
				return (tot);
			tot++;
		}
		else
			i++;
	}
	return (tot);
}

size_t	ft_size_str_cmd(char *str, char c, size_t j)
{
	size_t	i;
	bool single_quote;
	bool double_quote;
	
	single_quote = 0;
	double_quote = 0;
	i = 0;
	printf("str start = %s\n", str);
	while (str[j] == ' ')
		j++;
	while (str[j])
	{
		printf(" char = %c\n", str[j]);
		if (str[j] == '"' && !single_quote)
		{
			str = remoce_char(str, j);
			printf("i =  %zu str = %s\n",i,  str);
			double_quote = !double_quote;
		}	
		else if (str[j] == '\'' && !double_quote)
		{
			str = remoce_char(str, j);
			printf("i = %zu str = %s\n", i, str);
			single_quote = !single_quote;
		}
		else if (str[j] == c && !single_quote && !double_quote)
			return (i);
		else
		{
			i++;
			j++;
		}
	}
	return (i + 1);
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
	size_t	nb_string;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	nb_string = ft_nb_string_cmd(str, c);
	strs = ft_alloc(sizeof(*strs) * (nb_string + 1), arena);
	if (!strs)
		return (0);
	while (i < nb_string)
	{
		printf("nb string = %zu\n", nb_string);
		while (str[j] && str[j] == c)
			j++;
		size_str = ft_size_str_cmd(str, c, j);
		printf("size str = %zu", size_str);
		strs[i] = ft_mallocsplit_cmd(strs, (size_str + 2), i, arena);
		k = 0;
		while (str[j] && k < size_str)
			strs[i][k++] = str[j++];
		strs[i++][k] = '\0';
		printf("	str = %s\n", strs[i - 1]);
		j++;
	}
	strs[i] = 0;
	printf("strs = %s\n", strs[0]);
	return (strs);
}
