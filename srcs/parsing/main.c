/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:28:44 by lorampon          #+#    #+#             */
/*   Updated: 2022/11/29 14:51:44 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int return_value = 0;

void ft_reset_sh(t_shell *sh)
{
	sh->is_piped = 0;
	sh->saved_previous_fd = 0;
	ft_free_arena(&sh->arena);
	//free list command and one use allocation for previous command line
}


int ft_init_sh(t_shell *sh, char **envp)
{
	sh->arena.data = malloc(10000);
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

	(void)ac;
	(void)argv;
	ft_init_sh(&sh, env);
	while (1)
	{
		ft_init_arena(&sh.arena, 1000);
		signal(SIGINT, &ft_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		buff = readline("minishell : ");
		if (!buff)
		{
			printf("exit\n");
			exit(0);
		}
		if (ft_strlen(buff) > 0)
		{
			add_history(buff);
			sh = ft_parsing(buff, env, &sh);
			ft_exec_loop(&sh);
			ft_reset_sh(&sh);
		}
		free(buff);
	}
	return (0);
}
