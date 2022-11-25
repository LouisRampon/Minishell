#include "../../includes/minishell.h"

void	*ft_alloc(size_t size, t_arena *arena)
{
	if (!arena)
		return (malloc(size));
	else
		return (ft_arena_alloc(arena, size));
}
