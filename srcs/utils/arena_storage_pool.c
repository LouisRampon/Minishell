#include "../../includes/minishell.h"

int 	ft_init_arena(t_arena *arena, size_t size)
{
	arena->cursor = 0;
	arena->size = size;
	arena->data = malloc(arena->size);
	if (!arena->data)
		return (-1);
	return (0);
}

void	ft_free_arena(t_arena *arena)
{
	free(arena->data);
	arena->size = 0;
	arena->cursor = 0;
}

void	ft_reset_arena(t_arena *arena)
{
	arena->cursor = 0;
}

void 	*ft_arena_alloc(t_arena *arena, size_t size)
{
	size_t temp;

	if (arena->cursor + size > arena->size)
		return (NULL);
	temp = arena->cursor;
	arena->cursor += size;
	return (arena->data + temp);
}
