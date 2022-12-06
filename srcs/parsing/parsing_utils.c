/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:59:49 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/05 14:02:36 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

int	ft_is_white_space(char c)
{
	if (!c)
		return (0);
	if (c == ' ')
		return (1);
	else if (c > 9 && c < 13)
		return (1);
	return (0);
}

int	ft_skip_space(char *str, int i)
{
	if (!str[i])
		return (i);
	while (str[i] && ft_is_white_space(str[i]))
		i++;
	return (i);
}

char	*remoce_char(char *str, size_t pos)
{
	while (str[pos + 1])
	{
		str[pos] = str[pos + 1];
		pos++;
	}
	str[pos] = '\0';
	return (str);
}

t_quote	is_in_quote(t_quote quote, char c)
{
	if (c == '"' && !quote._single)
		quote._double = !quote._single;
	else if (c == '\'' && !quote._double)
		quote._single = !quote._single;
	return (quote);
}
