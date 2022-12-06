/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:16:10 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:16:11 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_built_in(t_command *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (1);
	return (0);
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_check_validity(t_shell *sh)
{
	char	*path;
	char	*temp;
	char	*path_line;
	char	**path_tab;
	int		i;

	if (ft_strchr(sh->cmd->cmd[0],'/'))
	{
		sh->cmd->path = ft_strdup_arena(sh->cmd->cmd[0], sh->arena);
		return ;
	}
	i = -1;
	path_line = ft_env_get("PATH", sh->env);
	path_tab = ft_split_arena(path_line, ':', sh->arena);
	while (path_tab && path_tab[++i])
	{
		temp = ft_strjoin_arena(path_tab[i], "/", sh->arena);
		path = ft_strjoin_arena(temp, sh->cmd->cmd[0], sh->arena);
		if (access(path, X_OK | F_OK) == 0)
		{
			sh->cmd->path = ft_strdup_arena(path, sh->arena);
			return ;
		}
	}
	sh->cmd->path = ft_strdup_arena(sh->cmd->cmd[0], sh->arena);
}

void	ft_check_cmd(t_shell *sh)
{
	if (is_built_in(sh->cmd) == 1)
		return ;
	ft_check_validity(sh);
}
