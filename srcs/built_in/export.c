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

t_env	*ft_new_env_bis(char *str, t_env *ptr)
{
	t_env *env;
	char **temp;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->next = ptr;
	temp = ft_split(str, '=');
	env->name = temp[0];
	if (ft_check_char(str, '=') && !temp[1])
		env->value = ft_calloc(1,1);
	else
		env->value = temp[1];
	free(temp);
	return (env);
	//todo free and check error
}

void	ft_create_first_elem(t_shell *sh, char *envp)
{
	t_env	*new;

	new = NULL;
	if (!envp)
		return ;
	new = ft_new_env(envp);
	if (!new)
	{
		ft_free_env_list(sh->env, ft_env_lst_size(sh->env));
		ft_putstr_fd("malloc failure", 2);
	}
	else
		sh->env = new;
}

void	ft_inset_first_elem(t_shell *sh, char **cmd, t_arena *arena)
{
	int i;

	i = 1;
	if (cmd[i] && ft_parse_export_arg(cmd[i], arena, 1) == 1)
		ft_create_first_elem(sh, cmd[i]);
	if (cmd[i + 1])
	{
		while (cmd[i])
		{
			if (ft_parse_export_arg(cmd[i], arena, 1) == 1)
				ft_add_env(cmd[i], sh);
			else
				printf("bad identifier\n");
			i++;
		}
	}
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
	if (!sh->env)
	{
		ft_inset_first_elem(sh, ptr->cmd, &sh->arena);
		return ;
	}
	i = 1;
	while(ptr->cmd[i])
	{
		if (ft_parse_export_arg(ptr->cmd[i], &sh->arena, 1) == 1)
			ft_add_env(ptr->cmd[i], sh);
		else
			printf("bad identifier\n");
		i++;
	}
}
