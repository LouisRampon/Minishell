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

int ft_check_char(char *str, char c)
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

int ft_only_equal(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '=')
			count++;
		i++;
	}
	if (ft_strlen(str) == count)
		return (1);
	return (0);
}

int ft_check_valid_indentifier(char *str)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	if (ft_only_equal(str) == 1 || ft_isdigit(str[i]) == 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_' || str[i] == '=' || str[i] == 32)
			count++;
		i++;
	}
	if (count == ft_strlen(str))
		return (1);
	return (0);
}

int ft_parse_export_arg(char **tab)
{
	int 	i;

	i = 1;
	while (tab[i])
	{
		if (ft_check_valid_indentifier(tab[i]) == 1)
			return (1);
		else
			printf("bad identifier\n");
		i++;
	}
	return (0);
}

void	ft_export(t_shell *sh)
{
	t_command	*ptr;
	int 		i;

	if (!sh->cmd->cmd[1])
	{
		ft_print_export(sh);
		return;
	}
	ptr = sh->cmd;
	i = 1;
	while (ptr)
	{
		if (ft_parse_export_arg(ptr->cmd) == 1)
			ft_add_env(ptr->cmd[i], sh);
		i++;
		ptr = ptr->next;
	}
}
