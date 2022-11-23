/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:28:44 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/23 17:31:58 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **argv, char **env)
{
	char	*buff;
	t_command	*cmd;
	size_t	i = 0;
	int j = 0;
	
	(void)ac;
	(void)argv;
	buff = malloc(sizeof(buff) * 2048);
	if (!buff)
		return (0);
	while (1)
	{
		signal(SIGINT, &ft_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		buff = readline("minishell : ");
		if (!buff)
		{
			printf("exit\n");
			exit(0);
		}
		cmd = ft_parsing(buff, env);
		i = 0;
		// while (i < nb_pipe(buff) + 1)
		// {
		// 	printf("command %zu:\n", i);
		// 	while(cmd[i].arg[j])
		// 	{
		// 		printf("word[%d] = %s\n", j, cmd[i].arg[j]);
		// 		j++;
		// 	}
		// 	j = 0;
		// 	printf("fd_in = %d\n", cmd[i].fd_in);
		// 	printf("fd_out = %d\n", cmd[i].fd_out);
		// 	i++;
		// }
	}
	return (0);	
}