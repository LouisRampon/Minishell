/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:11:29 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/14 11:15:23 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_double_pipe(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i - 1] == '|' && str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	check_syntax(char *str)
{
	if (check_double_pipe(str))
		return (1);
	return (0);
}