/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:32:16 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/06 15:15:58 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

size_t	ft_nb_string_cmd(char *str, char c)
{
	size_t	i;
	size_t	tot;
	t_quote	quote;

	i = 0;
	tot = 1;
	i = ft_skip_space(str, i);
	quote._single = 0;
	quote._double = 0;
	while (str[i])
	{
		quote = is_in_quote(quote, str[i]);
		if (str[i] == c && !quote._double && !quote._single)
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
	t_quote	quote;

	i = 0;
	quote._single = 0;
	quote._double = 0;
	while (str[j])
	{
		if (str[j] == '"' && !quote._single)
		{
			str = remoce_char(str, j);
			quote._double = !quote._double;
		}	
		else if (str[j] == '\'' && !quote._double)
		{
			str = remoce_char(str, j);
			quote._single = !quote._single;
		}
		else if (str[j] == c && !quote._single && !quote._double)
			return (i);
		else
		{
			i++;
			j++;
		}
	}
	return (i + 1);
}

int	ft_split_cmd_help(char *str, char c, t_arena *arena, char **strs)
{
	size_t	j;
	size_t	size_str;
	char	*temp;

	j = 0;
	while (str[j] && str[j] == c)
		j++;
	size_str = ft_size_str_cmd(str, c, j);
	temp = ft_substr_arena(str, j, size_str, arena);
	if (!temp)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	while (ft_isalnum(str[j]))
		j++;
	j = ft_skip_space(str, j);
	*strs = temp;
	return (j);
}

char	**ft_split_cmd(char *str, char c, t_arena *arena)
{
	char	**strs;
	size_t	nb_string;
	size_t	i;
	size_t	j;

	if (!str)
		return (0);
	i = 0;
	nb_string = ft_nb_string_cmd(str, c);
	strs = ft_alloc(sizeof(*strs) * (nb_string + 1), arena);
	if (!strs)
		return (NULL);
	j = 0;
	while (i < nb_string)
	{
		j += ft_split_cmd_help(str + j, c, arena, strs + i);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
