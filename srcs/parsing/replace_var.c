/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:42:32 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/06 12:36:43 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char	*find_var_name(char *str, int i, t_arena *arena)
{
	size_t	size;
	size_t	j;
	char	*var_name;

	j = 0;
	size = ft_strlen_alnum(&str[i]);
	if (!size)
		return (NULL);
	var_name = ft_alloc(sizeof(char) * (size + 1), arena);
	if (!var_name)
		return (str);
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
	int		i;
	t_env	*temp;

	i = 0;
	temp = env;
	printf("varname = %s\n", var_name);
	while (temp->next)
	{
		if (!ft_strncmp(temp->name, var_name, ft_strlen(var_name) + 1))
			return (temp->value);
		temp = temp->next;
	}
	if (!ft_strncmp(temp->name, var_name, ft_strlen(var_name)))
		return (temp->value);
	return ("\0");
}

char	*ft_fill_final(char *str, char *var, int size, t_arena *arena)
{
	int		j;
	int		i;
	int		k;
	char	*final;

	j = 0;
	final = ft_alloc(sizeof(final) * (size + 1), arena);
	while (str[j] != '$')
	{
		final[j] = str[j];
		j++;
	}
	k = 0;
	i = j + 1;
	while (var[k])
		final[j++] = var[k++];
	while (ft_isalnum(str[i]))
		i++;
	while (str[i] && j < size)
		final[j++] = str[i++];
	final[j] = '\0';
	return (final);
}

char	*replace_var_final(char *str, t_shell *shell, int i)
{
	char	*var_name;
	char	*var_value;
	char	*final;
	int		size;

	size = 0;
	var_name = find_var_name(str, i + 1, shell->arena);
	if (!var_name)
		return (str);
	var_value = replace_var_help(var_name, shell->env);
	if (var_value)
	{
		size = ft_strlen(str) - ft_strlen(var_name) + ft_strlen(var_value) + 1;
		final = ft_fill_final(str, var_value, size, shell->arena);
	}
	else
	{
		size = ft_strlen(str) - ft_strlen(var_name) + 1;
		final = ft_fill_final(str, NULL, size, shell->arena);
	}
	return (final);
}

char	*replace_var(char *str, t_shell *shell)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote._single = 0;
	quote._double = 0;
	while (str[i])
	{
		quote = is_in_quote(quote, str[i]);
		if (str[i] == '$' && !quote._single)
		{
			if (!str[i + 1])
				return (str);
			if (str[i + 1] == '?')
				str = ft_fill_final(str, ft_itoa(g_return_value),
						ft_strlen(ft_itoa(g_return_value)), shell->arena);
			else
				str = replace_var_final(str, shell, i);
			i++;
		}
		i++;
	}
	return (str);
}
