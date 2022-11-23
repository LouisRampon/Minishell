/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:29:21 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/23 16:13:29 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_clean_str_out_help(char *str, char *dest, int i, int j)
{
	int	k;

	k = 0;
	while(k < i)
		{
			dest[k] = str[k];
			k++; 
		}
		while(str[i + j])
		{
			dest[k] = str[i + j];
			i++;
			k++;
		}
		return (dest);
}

char *ft_clean_str_out(char *str)
{
	int	i;
	int	j;
	char *dest;
	
	i = 0;
	while (str[i] && str[i] != '>' && str[i] != '|')
		i++;
	if (str[i] == '>')
	{
		while (!ft_isalnum(str[i - 1]))
			i--;
		j = 0;
		while (str[i + j] && str[i + j] != '|')
			j++;
		dest = malloc(sizeof(char) * ft_strlen(str) - j + 1);
		if (!dest)
			return (0);
		return (ft_clean_str_out_help(str, dest, i, j));
	}
	else
		return (str);
}


char *ft_clean_str_in(char *str)
{
	int	i;
	int	j;
	char *dest;
	
	i = 0;
	j = 0;
	while (str[i] && str[i] != '<' && str[i] != '|')
		i++;
	if (str[i] == '<')
	{
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
			i++;
		dest = malloc(sizeof(char) * ft_strlen(str) - j + 1);
		if (!dest)
			return (0);
		while (str[i])
		{
			dest[j] = str[i];
			i++;
			j++;
		}
		dest[j] = '\0';
		return (dest);
	}
	else
		return (str);
}


char *ft_clean_str_to_pipe(char *str)
{
	int	i;
	int	j;
	char *temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * ft_strlen(str) - ft_strlen_to_c(str, '|') + 1);
	if (!temp)
		return (0);
	while (str[i] && str[i] != '|')
		i++;
	i++;
	while (str[i])
	{
		temp[j] = str[i];
		i++;
		j++;
	}
	return (temp);
}