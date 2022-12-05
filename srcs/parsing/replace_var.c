/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:42:32 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/02 17:09:36 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char	*find_var_name(char *str, int i, t_arena *arena)
{
	size_t size;
	size_t j;
	char *var_name;

	j = 0;
	size = ft_strlen_alnum(&str[i]);
	//printf("size = %zu\n", size);
	var_name = ft_alloc(sizeof(char) * (size + 1), arena);
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

char	*replace_var_help(char *var_name, t_env *env)
{
	int	i;
	t_env *temp;

	i = 0;
	temp = env;
	while(temp->next)
	{
		if (!ft_strncmp(temp->name, var_name, ft_strlen(var_name) + 1))
		{
			//printf("temp value =%s\n", temp->value);
			return (temp->value);
		}
		temp = temp->next;
	}
	if (!ft_strncmp(temp->name, var_name, ft_strlen(var_name)))
	{
	//	printf("temp value =%s\n", temp->value);
		return (temp->value);
	}
	return ("\0");
}

char *ft_fill_final(char *str, char *var, int size, int i, t_arena *arena)
{
	int j;
	int k;
	char *final;

	j = 0;
	final = ft_alloc(sizeof(final) * (size + 1), arena);
	while (str[j] != '$')
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

char	*replace_var_final(char *str, t_shell *shell, int i)
{
	char *var_name;
	char *var_value;
	char *final;
	int size;
	
	size = 0;
	var_name = find_var_name(str, i + 1, &shell->arena);
	//printf("var_name = %s\n", var_name);
	var_value = replace_var_help(var_name, shell->env);
	//printf("var_value = %s\n", var_value);
	if (var_value)
	{
		size = ft_strlen(str) - ft_strlen(var_name) + ft_strlen(var_value) + 1;
		final = ft_fill_final(str, var_value, size, i, &shell->arena);
	}
	else
	{
		size = ft_strlen(str) - ft_strlen(var_name) + 1;
		final = ft_fill_final(str, NULL, size, i, &shell->arena);
	}
	return (final);
}

char	*replace_var(char *str, t_shell *shell)
{
	int	i;
	bool single_quote;
	bool double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while(str[i])
	{
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (str[i] == '$' && !single_quote)
		{
			if (!str[i + 1])
				return (str);
			if (str[i + 1] == '?')
				str = ft_fill_final(str, ft_itoa(g_return_value), 
					ft_strlen(ft_itoa(g_return_value)), i, &shell->arena);
			else
				str = replace_var_final(str, shell, i);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}