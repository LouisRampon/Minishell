#include "../../includes/minishell.h"

void	ft_exit(char **av)
{
	for (int i = 0; av[i]; i++) {
		printf("%s", av[i]);
	}
	printf("\n");
}