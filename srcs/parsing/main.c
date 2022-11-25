/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:28:44 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/25 15:14:40 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int return_value = 0;

void ft_reset_sh(t_shell *sh)
{
	sh->is_piped = 0;
	sh->saved_previous_fd = 0;
	//free list command and one use allocation for previous command line
}


int ft_init_sh(t_shell *sh, char **envp)
{
	sh->arena.data = malloc(1000000);
	sh->is_piped = 0;
	sh->cpy_envp = envp;
	sh->saved_previous_fd = 0;
	sh->saved_pwd = NULL;
	sh->dup_std_fd[0] = dup(0);
	sh->dup_std_fd[1] = dup(1);
	ft_create_env_list(sh, envp);
	ft_update_saved_pwd(sh, ft_env_get("PWD", sh->env));
	return (1);
}

int	main(int ac, char **argv, char **env)
{
	char		*buff;
	t_shell		sh;
//	size_t	i = 0;
//	int j = 0;
	
	(void)ac;
	(void)argv;
	buff = malloc(sizeof(buff) * 2048);
	if (!buff)
		return (0);
	ft_init_sh(&sh, env);
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
		sh.cmd = ft_parsing(buff, env, sh.cmd);
		printf("fd_in = %d\n fd_out = %d\n", sh.cmd->fd_in, sh.cmd->fd_out);
		ft_exec_loop(&sh);
		ft_reset_sh(&sh);

		// while (cmd->next)
		// {
		// 	printf("command %zu:\n", i);
		// 	while(cmd->cmd[j])
		// 	{
		// 		printf("word[%d] = %s\n", j, cmd->cmd[j]);
		// 		j++;
		// 	}
		// 	j = 0;
		// 	printf("fd_in = %d\n", cmd->fd_in);
		// 	printf("fd_out = %d\n", cmd->fd_out);
		// 	i++;
		// 	cmd = cmd->next;
		// }
		// printf("command %zu:\n", i);
		// while(cmd->cmd[j])
		// {
		// 	printf("word[%d] = %s\n", j, cmd->cmd[j]);
		// 	j++;
		// }
		// j = 0;
		// printf("fd_in = %d\n", cmd->fd_in);
		// printf("fd_out = %d\n", cmd->fd_out);
	}
	return (0);	
}