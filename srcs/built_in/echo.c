/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:14:53 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:14:55 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_param(char **av, int *new_line)
{
	int	i;
	int	j;

	i = 1;
	while (av[i] && av[i][0] == '-' && av[i][1] == 'n')
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] == '\0')
		{
			*new_line = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	ft_echo(char **av)
{
	int	i;
	int	new_line;

	g_return_value = 0;
	new_line = 1;
	i = check_param(av, &new_line);
	while (av[i])
	{
		ft_putstr(av[i]);
		i += 1;
		if (av[i])
			ft_putchar(' ');
	}
	if (new_line == 1)
		ft_putchar('\n');
}
