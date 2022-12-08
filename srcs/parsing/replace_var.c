/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:42:32 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/07 16:14:30 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char	*find_var_name(char *str, int i, t_arena *arena)
{
	size_t	size;
	size_t	j;
	char	*var_name;
	t_quote	quote;

	quote._single = 0;
	quote._double = 0;
	j = 1;
	size = ft_strlen_alnum(&str[i]) + 1;
	var_name = ft_alloc(sizeof(char) * (size + 1), arena);
	var_name[0] = '$';
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
	t_env	*temp;

	temp = env;
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

char	*ft_fill_final(char *str, char *var_name, char *var_val, t_arena *arena)
{
	char	*final;

	final = ft_strnstr(str, var_name, ft_strlen(str));
	str = ft_substr_arena(str, 0, (ft_strlen(str) - ft_strlen(final)), arena);
	final = ft_substr_arena(final, ft_strlen(var_name),
			ft_strlen(final) - ft_strlen(var_name), arena);
	final = ft_strjoin_arena(var_val, final, arena);
	final = ft_strjoin_arena(str, final, arena);
	final[ft_strlen(final)] = '\0';
	return (final);
}

char	*replace_var_final(char *str, t_shell *shell, int i)
{
	char	*var_name;
	char	*var_value;

	var_name = find_var_name(str, i + 1, shell->arena);
	var_value = replace_var_help(var_name + 1, shell->env);
	if (var_value)
		str = ft_fill_final(str, var_name, var_value, shell->arena);
	else
		str = ft_fill_final(str, var_name, NULL, shell->arena);
	return (str);
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
				str = ft_fill_final(str, "$?", \
				ft_itoa_arena(g_return_value, shell->arena), shell->arena);
			else
				str = replace_var_final(str, shell, i);
			i = 0;
		}
		if (!ft_strlen(str))
			return (NULL);
		i++;
	}
	return (str);
}
