/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:42:32 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/23 15:30:56 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_var_name(char *str, int i)
{
	size_t k;
	size_t j;
	char *var_name;

	j = 0;
	k = ft_strlen_alnum(&str[i]);
	var_name = malloc(sizeof(char) * ft_strlen_alnum(str) + 1);
	if (!var_name)
		return (0);
	while (j < k)
	{
		var_name[j] = str[i];
		j++;
		i++;
	}
	return (var_name);
}

char	*replace_var_help(char *var_name, char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], var_name, ft_strlen(var_name)))
			return (&env[i][ft_strlen(var_name) + 1]);
		i++;
	}
	return ("\0");
}

char *ft_fill_final(char *str, char *var, int size, int i)
{
	int j;
	int k;
	char *final;

	j = 0;
	final = malloc(sizeof(final) * size + 1);
	while (j < i)
	{
		final[j] = str[j];
		j++;
	}
	k = 0;
	while (var[k])
	{
		final[j] = var[k];
		k++;
		j++;
	}
	i++;
	while (ft_isalnum(str[i]))
	{
		i++;
	}
	while (j < size)
	{
		final[j] = str[i];
		i++;
		j++;
	}
	return (final);
}

char	*replace_var(char *str, char **env)
{
	int	i;
	int size;
	char *var_name;
	char *var_value;
	char *final;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] != '\'' && str[i + 1])
		{
			var_name = find_var_name(str, i + 1);
			var_value = replace_var_help(var_name, env);
			if (var_value)
			{
				size = ft_strlen(str) - ft_strlen(var_name) + ft_strlen(var_value);
				final = ft_fill_final(str, var_value, size, i);
			}
			else
			{
				size = ft_strlen(str) - ft_strlen(var_name);
				final = ft_fill_final(str, 0, size, i);
			}
			str = final;
			i = -1;
			var_value = 0;
			free(var_name);
		}
		i++;
	}
	return (final);
}