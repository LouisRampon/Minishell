/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:42:26 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/07 12:55:02 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_multiple_newline(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (i > 2 && str[i - 2] == '>' && str[i - 1] == '>' && str[i] == '>')
			return (1);
		if (i > 2 && str[i - 2] == '<' && str[i - 1] == '<' && str[i] == '<')
			return (2);
		i++;
	}
	return (0);
}

int	check_double_pipe(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i - 1] == '|' && str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	check_quote(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (quote == 0)
				quote = 1;
			else if (quote == 1)
				quote = 0;
		}
		if (str[i] == '\'')
		{
			if (quote == 0)
				quote = 2;
			else if (quote == 2)
				quote = 0;
		}
		i++;
	}
	return (quote);
}

int	check_before_pipe(char *str, int i)
{
	if (i == 0)
		return (1);
	while (i > 0)
	{
		if (ft_isalnum(str[i]))
			return (0);
		i--;
	}
	return (1);
}

int	check_after_pipe(char *str, int i)
{
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
