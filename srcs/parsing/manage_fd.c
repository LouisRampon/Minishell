/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:28:26 by lorampon          #+#    #+#             */
/*   Updated: 2022/12/01 13:54:15 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fd_in(char *str)
{
	int fd;
	int	i;
	bool single_quote;
	bool double_quote;
	
	single_quote = 0;
	double_quote = 0;
	i = 0;
	fd = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;		
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (str[i] == '<' && !single_quote && !double_quote)
		{
			if (!str[i + 1])
			{	
				ft_error_msg(SYNTAX_ERROR);
				return (-1);
			}
			i++;
			while(str[i] == ' ')
				i++;
			fd = ft_fd_out_help(str, fd, i, 0);
			if (fd == -1)
				return (-1);
			while (ft_isalnum(str[i]))
				i++;
		}
		if (str[i])
			i++;
	}
	return (fd);
}

bool	ft_check_file(char *file_name, bool is_out)
{
	if(!is_out && access(file_name, F_OK))
	{
		dprintf(2, "minishell: %s %s\n", file_name, strerror(errno));
		// perror("minishell");
		// printf("minishell: %s: No such file or directory\n" ,file_name);
		return (1);
	}
	else if(!is_out && access(file_name, R_OK))
	{
		printf("minishell: %s: Permission denied\n" ,file_name);
		return (1);
	}
	else if (is_out && access(file_name, F_OK))
		return (0);
	else if (is_out && access(file_name, W_OK))
	{
		printf("minishell: %s: Permission denied\n" ,file_name);
		return (1);
	}
	return (0);
}

int	ft_fd_out_help(char *str, int fd, int i, bool is_out)
{
	int size;
	char *file_name;
	int	j;

	j = 0;
	if (str[i] != '\'' && str[i] != '\"')
		size = ft_strlen_alnum(&str[i]);
	else
	{
		size = ft_strlen_to_c(&str[i + 1], str[i]);
		i++;
	}
	file_name = malloc(sizeof(char) * size + 1);
	if (!file_name)
		return (-2);
	while (str[i] && j < size)
	{
		file_name[j] = str[i];
		i++;
		j++;
	}
	file_name[j] = '\0';
	if (fd > 2)
		close(fd);
	if (ft_check_file(file_name, is_out))
		return (-1);
	if (is_out)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_name, O_RDONLY | O_CREAT, S_IRWXU);
	free(file_name);
	return (fd);
}

int	ft_fd_out(char *str)
{
	int fd;
	int	i;
	bool single_quote;
	bool double_quote;
	
	single_quote = 0;
	double_quote = 0;
	i = 0;
	fd = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '"' && !single_quote)
			double_quote = !double_quote;		
		if (str[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (str[i] == '>' && !single_quote && !double_quote)
		{
			if (!str[i + 1])
			{	
				ft_error_msg(SYNTAX_ERROR);
				return (-1);
			}
			i++;
			while(str[i] == ' ')
				i++;
			fd = ft_fd_out_help(str, fd, i, 1);
			if (fd == -1)
				return (-1);
			while (ft_isalnum(str[i]))
				i++;
		}
		if (str[i])
			i++;
	}
	return (fd);
}