#include "../../includes/minishell.h"

void	ft_cd(t_shell *sh)
{
	chdir(sh->cmd->cmd[1]);
	ft_update_saved_pwd(sh, sh->cmd->cmd[1]);
}