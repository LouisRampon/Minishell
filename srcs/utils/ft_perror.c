/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:48 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:19:50 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_perror(char *cmd, char *input, char *status, int r_value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(status, 2);
	ft_putstr_fd("\n", 2);
	g_return_value = r_value;
}
