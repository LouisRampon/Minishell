/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:28:26 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/05 15:56:53 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fd_in(char *str)
{
	int		fd;
	int		i;
	t_quote	quote;

	i = 0;
	quote._single = 0;
	quote._double = 0;
	fd = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		quote = is_in_quote(quote, str[i]);
		if (str[i] == '<' && !quote._single && !quote._double)
		{
			fd = ft_fd_help(str, fd, i, ft_def_param_in(&str[i]));
			if (fd == -1)
				return (-1);
		}
		i++;
	}
	return (fd);
}

int	ft_fd_help(char *str, int fd, int i, int param)
{
	int		size;
	char	*file_name;
	int		j;

	j = 0;
	if (param > 1)
		i += 2;
	else
		i++;
	i = ft_skip_space(str, i);
	if (str[i] != '\'' && str[i] != '\"')
		size = ft_strlen_alnum(&str[i]);
	else
	{
		size = ft_strlen_to_c(&str[i + 1], str[i]);
		i++;
	}
	file_name = ft_substr(str, i, size);
	if (fd > 2)
		close(fd);
	if (ft_check_file(file_name, param))
		return (-1);
	return (ft_open_file(file_name, param));
}

int	ft_fd_out(char *str)
{
	int		fd;
	int		i;
	t_quote	quote;

	i = 0;
	quote._single = 0;
	quote._double = 0;
	fd = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		quote = is_in_quote(quote, str[i]);
		if (str[i] == '>' && !quote._single && !quote._double)
		{
			fd = ft_fd_help(str, fd, i, ft_def_param_out(&str[i]));
			if (fd == -1)
				return (-1);
		}
		i++;
	}
	return (fd);
}
