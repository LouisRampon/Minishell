/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:54:03 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/06 17:53:43 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_def_param_in(char *str)
{
	if (!str[1])
	{
		ft_error_msg(SYNTAX_ERROR);
		return (-1);
	}
	if (str[1] == '<')
		return (3);
	else
		return (0);
}

int	ft_def_param_out(char *str)
{
	if (!str[1])
	{
		ft_error_msg(SYNTAX_ERROR);
		return (-1);
	}
	if (str[1] == '>')
		return (2);
	else
		return (1);
}

int	ft_open_file(char *file_name, t_shell *shell)
{
	int	fd;

	if (shell->param == 3)
		fd = ft_heredoc(file_name, shell);
	else if (shell->param == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (shell->param == 1)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_name, O_RDONLY | O_CREAT, S_IRWXU);
	free(file_name);
	return (fd);
}

bool	ft_check_file(char *file_name, int is_out)
{
	if (!is_out && access(file_name, F_OK))
	{
		perror("minishell:");
		g_return_value = EXIT_FAILURE;
		return (1);
	}
	else if (!is_out && access(file_name, R_OK))
	{
		perror("minishell:");
		g_return_value = EXIT_FAILURE;
		return (1);
	}
	else if (is_out && access(file_name, F_OK))
		return (0);
	else if (is_out && access(file_name, W_OK))
	{
		perror("minishell:");
		g_return_value = EXIT_FAILURE;
		return (1);
	}
	return (0);
}
