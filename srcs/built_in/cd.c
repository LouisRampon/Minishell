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

void	ft_update_env(t_shell *sh, int flag)
{
	char	*env_str;
	char 	*buff;

	if (flag == 1)
	{
		env_str = ft_strjoin("OLDPWD=", sh->saved_pwd);
		if (!env_str)
			return ;
		ft_add_env(env_str, sh);
		free(env_str);
	}
	else
	{
		buff = getcwd(NULL, 0);
		env_str = ft_strjoin("PWD=", buff);
		if (!env_str)
			return ;
		ft_add_env(env_str, sh);
		free(buff);
		free(env_str);
	}
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
		ft_update_env(sh, 1);
	ptr2 = ft_env_get_struct("PWD", sh->env);
	if (ptr2)
		getcwd(ptr2->value, 4096);
	else
		ft_update_env(sh, 2);
	getcwd(sh->saved_pwd, 4096);
}

void	ft_go_home(t_shell *sh)
{
	if (chdir(sh->home) == -1)
		printf("minishell: cd ~: Home doesn't exits\n");
	else
		chdir(sh->home);
}

void	ft_cd(t_shell *sh)
{
	if (!sh->cmd->cmd[1] || sh->cmd->cmd[1][0] == '~')
		ft_go_home(sh);
	else if (access(sh->cmd->cmd[1], X_OK | F_OK) != 0)
		printf("minishell: cd: *input*: Permission denied\n");
	else if (chdir(sh->cmd->cmd[1]) == -1)
		printf("minishell: cd: *input*: No such file or directory\n");
	ft_manage_pwd(sh);
}
