/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:28:26 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/24 15:24:39 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_fd_in(char *str)
{
	int fd;
	int	i;
	int size;
	char *file_name;
	int j;

	i = 0;
	j = 0;
	fd = 0;
	while (str[i])
	{
		if (str[i] ==  '<')
		{
			i++;
			while (str[i] == ' ')
				i++;
			size = ft_strlen_alnum(&str[i]);
			file_name = malloc(sizeof(char) * size + 1);
			if (!file_name)
				return (-1);
			while(j < size)
			{
				file_name[j] = str[i];
				i++;
				j++;
			}
			file_name[j] = '\0';
			if (fd > 2)
				close(fd);
			fd = open(file_name, O_RDWR);
			free(file_name);
			j = 0;
		}
		if (str[i])
			i++;
	}
	return (fd);
}

int	ft_fd_out(char *str)
{
	int fd;
	int	i;
	int	j;
	int size;
	char *file_name;

	i = 0;
	j = 0;
	fd = 1;
	while (str[i])
	{
		if (str[i] == '>')
		{
			i++;
			while(str[i] == ' ')
				i++;
			size = ft_strlen_alnum(&str[i]);
			file_name = malloc(sizeof(char) * size + 1);
			if (!file_name)
				return (-1);
			while (j < size)
			{
				file_name[j] = str[i];
				i++;
				j++;
			}
			file_name[j] = '\0';
			//printf("%s\n", file_name);
			if (fd > 2)
				close(fd);
			fd = open(file_name, O_RDWR | O_CREAT, S_IRWXU);
			free(file_name);
			j = 0;
		}
		if (str[i])
			i++;
	}
	return (fd);
}