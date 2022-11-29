/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:30:08 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/29 13:57:50 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

size_t nb_pipe(char *str)
{
	size_t	i;
	size_t	pipe;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_pass_quote(str, i);
		if (str[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

size_t	ft_strlen_to_c(char *str, char c)
{
	size_t i;
	
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

size_t	ft_strlen_alnum(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_pass_quote(const char *str, int i)
{
	char c;
	int	temp;
	
	temp = i;
	c = str[i];
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (temp);
}
