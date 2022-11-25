/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:29:21 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/25 12:43:49 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_clean_str(char *str)
{
	int last_fd_in;
	size_t len;
	int last_fd_out;
	char *temp;
	
	last_fd_in = 0;
	while (str[last_fd_in] && str[last_fd_in] == ' ')
		last_fd_in++;
	if (str[last_fd_in] == '<')
	{	
		last_fd_in++;
		while (str[last_fd_in] && str[last_fd_in] == ' ')
			last_fd_in++;
		while (str[last_fd_in] && ft_isalnum(str[last_fd_in]))
			last_fd_in++;
		while (str[last_fd_in] && str[last_fd_in] == ' ')
			last_fd_in++;
	}
	last_fd_out = ft_strlen_to_c(str, '>');
	len = last_fd_out - last_fd_in;
	temp = ft_substr(str, last_fd_in, len);
	return (temp);
}
