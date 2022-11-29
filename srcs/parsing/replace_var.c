/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:42:32 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/29 13:56:47 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char	*find_var_name(char *str, int i)
{
	size_t size;
	size_t j;
	char *var_name;

	j = 0;
	size = ft_strlen_alnum(&str[i]);
	printf("size = %zu\n", size);
	var_name = malloc(sizeof(char) * size + 1);
	if (!var_name)
		return (0);
	while (str[i] && j < size)
	{
		var_name[j] = str[i];
		j++;
		i++;
	}
	var_name[j] = '\0';
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
		i++;
	while (str[i] && j < size)
	{
		final[j] = str[i];
		i++;
		j++;
	}
	final[j] = '\0';
	return (final);
}

char	*replace_var_final(char *str, char **env, int i)
{
	char *var_name;
	char *var_value;
	char *final;
	int size;
	
	size = 0;
	var_name = find_var_name(str, i + 1);
	//printf("var_name = %s\n", var_name);
	var_value = replace_var_help(var_name, env);
	//printf("var_value = %s\n", var_value);
	if (var_value)
	{
		size = ft_strlen(str) - ft_strlen(var_name) + ft_strlen(var_value) + 1;
		final = ft_fill_final(str, var_value, size, i);
	}
	else
	{
		size = ft_strlen(str) - ft_strlen(var_name) + 1;
		final = ft_fill_final(str, 0, size, i);
	}
	free(var_name);
	return (final);
}

char	*replace_var(char *str, char **env)
{
	int	i;
	char *temp;

	i = 1;
	if (str[0] == '$')
	{
			temp = replace_var_final(str, env, 0);
			free(str);
			str = temp;
	}
	if (str[0] == '\'')
	{
		i = ft_pass_quote(str, i);
	}
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i = ft_pass_quote(str, i);
		}
		if (str[i] == '$' && str[i + 1])
		{
			temp = replace_var_final(str, env, i);
			str = temp;
			i = 0;
		}
		i++;
	}
	return (str);
}