/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:29:21 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/05 15:38:38 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_size_file_name(char *str)
{
	int	i;

	i = 0;
	i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

int	ft_clean_str_help(char *str, int i, t_quote quote)
{
	if ((str[i] == '>' && str[i + 1] == '>' )
		&& !quote._double && !quote._single)
		return (ft_size_file_name(&str[i + 1]) + 1);
	else if ((str[i] == '<' && str[i + 1] == '<')
		&& !quote._double && !quote._single)
		return (ft_size_file_name(&str[i + 1]) + 1);
	else if ((str[i] == '>' || str[i] == '<')
		&& !quote._double && !quote._single)
		return (ft_size_file_name(&str[i]));
	else
		return (0);
}

char	*ft_clean_str(char *str)
{
	int		i;
	int		j;
	t_quote	quote;

	i = 0;
	quote._single = 0;
	quote._double = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i + j])
	{
		quote = is_in_quote(quote, str[i + j]);
		j = ft_clean_str_help(str, i + j, quote) + j;
		str[i] = str[i + j];
		if (!(str[i] == '>' || str[i] == '<') || !quote._double || !quote._single)
			i++;
	}
	str[i] = '\0';
	return (str);
}
