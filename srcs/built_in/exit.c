/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:15:08 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:15:09 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

int	ft_only_digits(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			count++;
		i++;
	}
	if (i == count)
		return (1);
	return (0);
}

void	ft_exit(t_shell *sh)
{
	long  int	ret;

	ret = g_return_value;
	if (sh->cmd->cmd[0] && sh->cmd->cmd[1])
	{
		ret = ft_atoi(sh->cmd->cmd[1]);
		if (!ft_only_digits(sh->cmd->cmd[1]))
		{
			if (ret == -1 && ft_strlen(sh->cmd->cmd[1]) > 2)
			{
				printf("exit\n");
				ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
				g_return_value = 255;
				ret = 255;
			}
		}
		else if (sh->cmd->cmd[2])
		{
			printf("exit\n");
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_return_value = 1;
			return ;
		}
	}
	ft_free_env_list(sh->env, ft_env_lst_size(sh->env));
	ft_free_arena(sh->arena);
	exit((unsigned char)ret);
}
