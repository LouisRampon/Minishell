/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:46:47 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/23 16:47:15 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **ft_str_to_arg(char *str)
{
	char *temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char) * ft_strlen_to_c(str, '|') + 1);
	if (!temp)
		return (0);
	while(str[i] && str[i] != '|')
	{
		temp[i] = str[i];
		i++;
	}
	return(ft_split(temp, ' '));
}

t_command ft_fill_cmd(char *str, size_t i)
{
	t_command cmd;
	
	(void)i;
	cmd.fd_in = ft_fd_in(str);
	cmd.fd_out = ft_fd_out(str);
	str = ft_clean_str_out(str);
	str = ft_clean_str_in(str);
	//printf("str before arg = %s\n", str);
	cmd.arg = ft_str_to_arg(str);
	return (cmd);
}

t_command	*ft_parsing(char *str, char **env)
{
	t_command *cmd;
	size_t nb_cmd;
	size_t	i;
	int j = 0;
	
	i = 0;
	if (check_syntax(str))
		return (0);
	str = replace_var(str, env);
	nb_cmd = nb_pipe(str) + 1;
	cmd = malloc(sizeof(t_command) * nb_cmd + 1);
	if (!cmd)
		return (0);
	while (i < nb_cmd)
	{
		cmd[i] = ft_fill_cmd(str, i);
		str = ft_clean_str_to_pipe(str);
		j = 0;
		// while(cmd[i].arg[j])
		// {
		// 	printf("arg %zu = %s\n", i, cmd[i].arg[j]);
		// 	j++;
		// }
		// printf("fd_in = %d\n", cmd[i].fd_in);
		// printf("fd_out = %d\n", cmd[i].fd_out);
		i++;
	}
	return (cmd);
}
