/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:29:21 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/29 14:57:21 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_last_fd_out(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_pass_quote(str, i);
		if (str[i] == '>')
			return (i);
		i++;
	}
	return (i);
}

int ft_last_fd_in(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_pass_quote(str, i);
		if (str[i] == '<')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '\'' || str[i] == '\"')
				i = ft_pass_quote(str, i) + 1;
			else
				while (str[i] && ft_isalnum(str[i]))
					i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char *ft_clean_str(char *str, t_shell *shell)
{
	int last_fd_in;
	size_t len;
	int last_fd_out;
	char *temp;
	int	i;
	
	last_fd_in = 0;
	i = 0;
	last_fd_in = ft_last_fd_in(str);
	last_fd_out = ft_last_fd_out(str);
	len = last_fd_out - last_fd_in;
	temp = ft_substr_arena(str, last_fd_in, len, &shell->arena);
	return (temp);
}
