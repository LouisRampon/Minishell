#include "../../includes/minishell.h"

void	ft_unset(t_shell *sh)
{
	if(sh->cmd->cmd[1])
		ft_del_env(sh->cmd->cmd[1], sh);
}