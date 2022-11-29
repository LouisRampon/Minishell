/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:28:26 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/29 13:03:59 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fd_in(char *str)
{
	int fd;
	int	i;

	i = 0;
	fd = 1;
	printf("start\n");
	while (str[i])
	{
		printf("i avant = %d	", i);
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_pass_quote(str, i);
		printf("i apres = %d\n", i);
		// if (str[i] == '<')
		// {
		// 	i++;
		// 	while(str[i] == ' ')
		// 		i++;
		// 	fd = ft_fd_out_help(str, fd, i);
		// 	while (ft_isalnum(str[i]))
		// 		i++;
		// }
		if (str[i])
			i++;
	}
	printf("finish\n");
	return (fd);
}

int	ft_fd_out_help(char *str, int fd, int i)
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
		return (-1);
	while (str[i] && j < size)
	{
		file_name[j] = str[i];
		i++;
		j++;
	}
	file_name[j] = '\0';
	if (fd > 2)
		close(fd);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	free(file_name);
	return (fd);
}

int	ft_fd_out(char *str)
{
	int fd;
	int	i;

	i = 0;
	fd = 1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_pass_quote(str, i);
		if (str[i] == '>')
		{
			i++;
			while(str[i] == ' ')
				i++;
			fd = ft_fd_out_help(str, fd, i);
			while (ft_isalnum(str[i]))
				i++;
		}
		if (str[i])
			i++;
	}
	return (fd);
}