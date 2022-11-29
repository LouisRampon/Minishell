/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/29 14:59:30 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char **ft_trim_quote(char **strs, t_shell *shell)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i][0] == '\"' && strs[i][ft_strlen(strs[i]) - 1] == '\"')
			strs[i] = ft_substr_arena(strs[i], 1, ft_strlen(strs[i]) - 2, &shell->arena);
		i++;
	}
	return (strs);
}
char **ft_str_to_arg(char *str, t_shell *shell)
{
	char **temp;
	
	temp = ft_split_quote(str, ' ', &shell->arena);
	return(ft_trim_quote(temp, shell));
}


t_command *ft_fill_cmd(char *str, size_t i, t_shell *shell)
{
	t_command *cmd;
	
	(void)i;
	cmd = ft_alloc(sizeof(t_command), &shell->arena);
	cmd->fd_in = ft_fd_in(str);
	cmd->fd_out = ft_fd_out(str);
	str = ft_clean_str(str, shell);
	cmd->cmd = ft_str_to_arg(str, shell);
	cmd->next = NULL;
	return (cmd);
}

t_shell	ft_parsing(char *str, char **env, t_shell *shell)
{
	t_command *previous;
	t_command *new;
	char	**arg;
	size_t nb_cmd;
	size_t	i;

	i = 0;
	previous = NULL;
	new = NULL;
	if (check_syntax(str))
		return (*shell);
	str = replace_var(str, env, &shell->arena);
	nb_cmd = nb_pipe(str) + 1;
	arg = ft_split_quote(str, '|', &shell->arena);
	while (i < nb_cmd)
	{
		new = ft_fill_cmd(arg[i], i, shell);
		if (previous)
			previous->next = new;
		else
			shell->cmd = new;
		previous = new;
		i++;
	}
	return (*shell);
}
