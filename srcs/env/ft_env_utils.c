/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:16 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:15:17 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_char_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_only_char(char *str, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (ft_strlen(str) == count)
		return (1);
	return (0);
}

int	ft_check_valid_indentifier(char *str, int flag)
{
	int		i;

	i = 0;
	if (ft_only_char(str, '=') == 1 || ft_isdigit(str[i]) == 1)
		return (0);
	if (ft_check_char(str, '=') == 1 && flag == 2)
		return (0);
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && !str[i + 1]))
			return (1);
		if (!(ft_isalnum(str[i]) == 1 || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse_export_arg(char *str, t_arena *arena, int code)
{
	int		i;
	int		index;
	char	*temp;

	i = -1;
	while (str[++i])
	{
		index = ft_check_char_index(str, '=');
		if (index != -1)
		{
			temp = ft_substr_arena(str, 0, index, arena);
			if (temp && code == 1)
				return (ft_check_valid_indentifier(temp, code));
		}
		else
			return (ft_check_valid_indentifier(str, code));
	}
	return (0);
}
