/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:11:29 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/07 12:54:03 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char	check_pipe(char *str)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote._single = 0;
	quote._double = 0;
	while (str[i])
	{
		quote = is_in_quote(quote, str[i]);
		if (str[i] == '|' && !quote._double && !quote._single)
		{
			if (check_before_pipe(str, i) || check_after_pipe(str, i))
				return (str[i]);
		}
		i++;
	}
	return (0);
}

int	ft_error_msg(int error)
{
	if (error == SYNTAX_ERROR)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_return_value = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	return (0);
}

int	ft_check_redirection(char *str)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote._single = 0;
	quote._double = 0;
	while (str[i])
	{
		quote = is_in_quote(quote, str[i]);
		if (str[i] == '>' && !quote._double && !quote._single)
		{
			if (check_after_pipe(str, i))
				return (str[i]);
		}
		else if (str[i] == '<' && !quote._double && !quote._single)
		{
			if (check_after_pipe(str, i))
				return (str[i]);
		}
		i++;
	}
	return (0);
}

int	check_syntax_help(char *str)
{
	if (check_quote(str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected quote\n", 2);
		g_return_value = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	if (check_pipe(str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_return_value = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	if (ft_check_redirection(str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n"\
			, 2);
		g_return_value = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	return (0);
}

int	check_syntax(char *str)
{
	if (check_double_pipe(str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		g_return_value = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	if (check_multiple_newline(str) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
		g_return_value = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	if (check_multiple_newline(str) == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<<<'\n", 2);
		g_return_value = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	if (check_syntax_help(str))
		return (SYNTAX_ERROR);
	return (0);
}
