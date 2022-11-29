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

int	ft_check_validity(t_shell *sh)
{
	char	*path;
	char	*temp;
	char	*path_line;
	char	**path_tab;
	int		i;

	i = -1;
	path_line = ft_env_get("PATH", sh->env);
	path_tab = ft_split_arena(path_line, ':', &sh->arena);
	while (path_tab && path_tab[++i])
	{
		temp = ft_strjoin_arena(path_tab[i], "/", &sh->arena);
		path = ft_strjoin_arena(temp, sh->cmd->cmd[0], &sh->arena);
		if (access(path, X_OK | F_OK) == 0)
		{
			sh->cmd->path = ft_strdup_arena(path, &sh->arena);
			return (1);
		}
	}
	ft_free_arena(&sh->arena);
	return (0);
}

void	check_access(char *str, t_arena *arena)
{
	if (access(str, X_OK | F_OK) != 0)
	{
		perror("minishell: ");
		ft_free_arena(arena);
		exit(errno);
	}
}

char	*ft_concat_pwd_path(t_shell *sh, char *str)
{
	char	*temp;
	if (str[1])
	{
		temp = ft_strjoin_arena(sh->saved_pwd, str, &sh->arena);
		if (!temp)
		{
			ft_free_arena(&sh->arena);
			ft_perror_exit("Malloc failure", 1);
		}
		return (temp);
	}
	return (NULL);
}

int ft_check_absolute_path(t_shell *sh)
{
	if (sh->cmd->cmd[0][0] == '.')
	{
		check_access(ft_concat_pwd_path(sh, sh->cmd->cmd[0]), &sh->arena);
		return (1);
	}
	else if (sh->cmd->cmd[0][0] == '/')
	{
		check_access(sh->cmd->cmd[0], &sh->arena);
		return (1);
	}
	return (0);
}

int	ft_check_cmd(t_shell *sh)
{
	if (is_built_in(sh->cmd) == 1)
		return (1);
	if (ft_check_absolute_path(sh) == 1)
		return (1);
	return (ft_check_validity(sh));
}
