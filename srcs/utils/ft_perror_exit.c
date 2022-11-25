#include "../../includes/minishell.h"

void	ft_perror_exit(char *str, int code)
{
	printf("%s\n", str);
	exit(code);
}