/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:29:21 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/01 15:30:42 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_size_file_name(char *str, int i)
{
	char c;
	int	size;

	size = 0;
	c = str[i];
	i++;
	while (str[i] && str[i] == ' ')
	{
		i++;
		size++;
	}
	while (str[i] && ft_isalnum(str[i]))
	{
		size++;
		i++;
	}
	return (size + 1);
}

char *ft_clean_str(char *str)
{
	int	i;
	int	j;
	bool	single_quote;
	bool double_quote;
	
	single_quote = 0;
	double_quote = 0;
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i + j])
	{
		if (str[i + j] == '"' && !single_quote)
			double_quote = !double_quote;		
		else if (str[i + j] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (str[i + j] == '>' || str[i + j] == '<')
			j = ft_size_file_name(str, i + j) + j;
		//printf("%d\n", j);
		str[i] = str[i + j];
		i++;
	}
	str[i] = '\0';
	//printf("str = %s\n", str);
	return (str);
}
