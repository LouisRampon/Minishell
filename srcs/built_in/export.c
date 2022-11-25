#include "../../includes/minishell.h"

void	ft_print_export(t_shell *sh)
{
	char	**tab;
	char	*temp;
	int 	i;
	int		size;

	i = 0;
	size = ft_env_lst_size(sh->env);
	tab = ft_env_list_to_tab(sh);
	while (i < size - 1)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
	else
		i++;
	}
	i = -1;
	while (tab[++i])
		printf("declare -x %s\n", tab[i]);
	ft_free_tab(tab);
}

//int	ft_check_valid_identifier(char **cmd)
//{
//	int i;
//
//	i = 0;
//	while (cmd[i])
//	{
//		if ( )
//	}
//}

void	ft_export(t_shell *sh, char *cmd)
{
	t_command *ptr;
	(void) cmd;
	if (!sh->cmd->cmd[1])
	{
		ft_print_export(sh);
		return;
	}

	ptr = sh->cmd;
//	while(ptr)
//	{
//		if (ft_check_valid_identifier(ptr->cmd) == 1)
//		{
//
//		}
//		ptr = ptr->next;
//	}
//}


//		//m'occuper du cas ou il n'y a pas de =
//		if (ft_strchr(cmd, '='))
//		{
//			if (ft_check_valid_identifier(cmd) == 1)
//				ft_add_env(cmd, sh);
//		}
//		else
//			push_back_env(sh->env, cmd); //fix elem vide
}