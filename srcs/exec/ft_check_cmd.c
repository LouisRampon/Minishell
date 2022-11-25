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
	else
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
	path_tab = ft_split(path_line, ':');
	while (path_tab && path_tab[++i])
	{
		temp = ft_strjoin(path_tab[i], "/");
		path = ft_strjoin(temp, sh->cmd->cmd[0]);
		free(temp);
		if (access(path, X_OK | F_OK) == 0)
		{
			sh->cmd->path = ft_strdup(path);
			free(path);
			ft_free_tab(path_tab);
			//printf("%s\n", sh->cmd->path);
			return (1);
		}
		free(path);
	}
	ft_free_tab(path_tab);
	return (0);
}

void	check_access(char *str)
{
	if (access(str, X_OK | F_OK) != 0)
	{
		perror("minishell: ");
		//free arena pool
		exit(errno);
	}
}

char	*ft_concat_pwd_path(t_shell *sh, char *str)
{
	char	*temp;
	if (str[1])
	{
		temp = ft_strjoin(sh->saved_pwd, str);
		if (!temp)
			ft_perror_exit("Malloc failure", 1);
		return (temp);
	}
	return (NULL);
}

int ft_check_absolute_path(t_shell *sh)
{
	if (sh->cmd->cmd[0][0] == '.')
	{
		check_access(ft_concat_pwd_path(sh, sh->cmd->cmd[0]));
		return (1);
	}
	else if (sh->cmd->cmd[0][0] == '/')
	{
		check_access(sh->cmd->cmd[0]);
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