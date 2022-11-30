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

int	ft_only_digits(char *str)
{
	int i;
	int sign;
	int count;

	count = 0;
	sign = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			sign ++;
		if (ft_isdigit(str[i]) == 1)
			count++;
		i++;
	}
	if (i == count && sign == 1)
		return (1);
	return (0);
}

void	ft_exit(t_shell *sh)
{
	 long int ret;

	ret = return_value;
	printf("exit\n");
	if (sh->cmd->cmd[0] && sh->cmd->cmd[1])
	{
		if (!ft_only_digits(sh->cmd->cmd[1]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			return_value = 255;
			ret = 255;
		}
		else if (sh->cmd->cmd[2])
		{
			ft_putstr_fd("minishell: exit:too many arguments\n", 2);
			return_value = 1;
			return ;
		}
		ret = ft_atoi(sh->cmd->cmd[1]);
	}
	ft_free_env_list(sh->env, ft_env_lst_size(sh->env));
	ft_free_arena(&sh->arena);
	exit((int)ret);
}
