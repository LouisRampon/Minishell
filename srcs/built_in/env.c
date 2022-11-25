#include "../../includes/minishell.h"

void	ft_env(t_shell *sh)
{
	t_env	*ptr;

	//protect env
	if (sh->env)
	{
		ptr = sh->env;
		while (ptr)
		{
			if (ptr->name && ptr->value)
				printf("%s=%s\n", ptr->name, ptr->value);
			ptr = ptr->next;
		}
	}
}
