/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:53 by jereverd          #+#    #+#             */
/*   Updated: 2022/12/01 14:00:42 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror_exit(char *cmd, char *input, char *status, int r_value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(status, 2);
	ft_putstr_fd("\n", 2);
	exit(g_return_value = r_value);
}
