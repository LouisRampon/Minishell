/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/07 16:23:10 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"

char	**ft_str_to_arg(char *str, t_shell *shell)
{
	char	**temp;

	temp = ft_split_cmd(str, ' ', shell->arena);
	return (temp);
}

t_command	*ft_fill_cmd(char *str, t_shell *shell)
{
	t_command	*cmd;

	if (!str)
		return (NULL);
	cmd = ft_alloc(sizeof(t_command), shell->arena);
	if (!cmd)
		return (NULL);
	cmd->fd_in = ft_fd_in(str, shell);
	if (cmd->fd_in == -1)
		return (NULL);
	cmd->fd_out = ft_fd_out(str, shell);
	if (cmd->fd_out == -1)
		return (NULL);
	str = ft_clean_str(str);
	str = replace_var(str, shell);
	cmd->cmd = ft_str_to_arg(str, shell);
	if (!cmd->cmd)
		return (NULL);
	cmd->next = NULL;
	return (cmd);
}

t_command	*ft_fill_list(char **arg, t_shell *shell, size_t nb_cmd)
{
	size_t		i;
	t_command	*head;
	t_command	*previous;
	t_command	*new;

	i = 0;
	previous = NULL;
	new = NULL;
	while (i < nb_cmd)
	{
		new = ft_fill_cmd(arg[i], shell);
		if (!new)
			return (head);
		if (previous)
			previous->next = new;
		else
			head = new;
		previous = new;
		i++;
	}
	return (head);
}

t_shell	ft_parsing(char *str, t_shell *shell)
{
	char		**arg;
	size_t		nb_cmd;

	if (check_syntax(str))
		return (*shell);
	nb_cmd = nb_pipe(str) + 1;
	arg = ft_split_quote(str, '|', shell->arena);
	shell->cmd = ft_fill_list(arg, shell, nb_cmd);
	return (*shell);
}
