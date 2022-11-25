#include "../../includes/minishell.h"

t_env	*ft_new_env(char *envp)
{
	t_env *env;
	char **temp;

	env = malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->next = NULL;
	temp = ft_split(envp, '=');
	env->name = temp[0];
	env->value = temp[1];
	return (env);
}

int	ft_env_lst_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

//to fix
void	ft_free_env_list(t_env *env, int size)
{
	t_env *tmp;
	int i;

	i = 0;
	while (i < size)
	{
		tmp = env->next;
		free(env);
		env = NULL;
		env = tmp;
		i++;
	}
}

void	ft_create_env_list(t_shell *sh, char **envp)
{
	int		i;
	t_env	*previous;
	t_env	*new;

	previous = NULL;
	new = NULL;
	i = 0;
	while (envp[i])
	{
		new = ft_new_env(envp[i]);
		if (!new)
		{
			//fix free_env_list
			ft_free_env_list(sh->env, ft_env_lst_size(sh->env));
			ft_putstr_fd("malloc failure", 2);
		}
		if (previous)
			previous->next = new;
		else
			sh->env = new;
		previous = new;
		i++;
	}
}