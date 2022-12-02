/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:11:29 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/02 13:26:56 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int check_quote(char *str)
{
	int	i;
	int quote;

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



int	ft_error_msg(int error)
{
	if (error == SYNTAX_ERROR)
	{
		printf("minishell: syntax error\n");
		return(SYNTAX_ERROR);
	}
	return (0);
}
int	check_syntax(char *str)
{
	if (check_double_pipe(str))
		return (ft_error_msg(SYNTAX_ERROR));
	if (check_quote(str))
		return (ft_error_msg(SYNTAX_ERROR));
	// if (check_pipe(str))
	// 	return (ft_error_msg(SYNTAX_ERROR));
	return (0);
}