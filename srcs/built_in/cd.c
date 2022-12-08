/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:14:47 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:14:49 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_pwd(t_shell *sh)
{
	char	*env_str;
	char	*buff;

	buff = getcwd(NULL, 0);
	env_str = ft_strjoin("PWD=", buff);
	if (!env_str)
		return ;
	if (sh->env)
		ft_add_env(env_str, sh);
	else
	{
		ft_create_first_elem(sh, env_str);
		ft_add_env(env_str, sh);
	}
	free(buff);
	free(env_str);
}

void	ft_update_oldpwd(t_shell *sh)
{
	char	*env_str;

	env_str = ft_strjoin("OLDPWD=", sh->saved_pwd);
	if (!env_str)
		return ;
	if (sh->env)
		ft_add_env(env_str, sh);
	else
	{
		ft_create_first_elem(sh, env_str);
		ft_add_env(env_str, sh);
	}
	free(env_str);
}

void	ft_manage_pwd(t_shell *sh)
{
	t_env	*ptr;
	t_env	*ptr2;

	ptr = ft_env_get_struct("OLDPWD", sh->env);
	if (ptr)
	{
		free(ptr->value);
		ptr->value = ft_strdup(sh->saved_pwd);
	}
	else
		ft_update_oldpwd(sh);
	ptr2 = ft_env_get_struct("PWD", sh->env);
	if (ptr2)
	{
		free(ptr2->value);
		ptr2->value = getcwd(0, 4096);
	}
	else
		ft_update_pwd(sh);
	getcwd(sh->saved_pwd, 4096);
}

void	ft_cd(t_shell *sh)
{
	if (!sh->cmd->cmd[1] || sh->cmd->cmd[1][0] == '~')
	{
		if (chdir(sh->home) == -1)
		{
			ft_perror("cd: ", sh->cmd->cmd[1], "Home doesn't exist", 1);
			return ;
		}
	}
	else if (chdir(sh->cmd->cmd[1]) == -1)
	{
		if (access(sh->cmd->cmd[1], F_OK) != 0)
			ft_perror("cd: ", sh->cmd->cmd[1], "No such file or directory", 1);
		else if (access(sh->cmd->cmd[1], X_OK | R_OK) != 0)
			ft_perror("cd: ", sh->cmd->cmd[1], "Permission denied", 1);
		return ;
	}
	g_return_value = 0;
	ft_manage_pwd(sh);
}
