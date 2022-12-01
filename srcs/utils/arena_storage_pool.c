/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_storage_pool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:44 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:19:45 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_arena_realloc(t_arena *arena, size_t size)
{
	void *tmp;
	size_t oldsize;

	oldsize = arena->size;
	tmp = arena->data;
	if (size + arena->size > arena->size * 2)
		arena->size = size + arena->size * 2;
	else
		arena->size *= 2;
	arena->data = malloc(arena->size);
	ft_memcpy(arena->data, tmp, oldsize);
	free(tmp);
	//todo error
}

void 	*ft_arena_alloc(t_arena *arena, size_t size)
{
	size_t temp;

	if (arena->cursor + size > arena->size)
		ft_arena_realloc(arena, size);
	temp = arena->cursor;
	arena->cursor += size;
	return (arena->data + temp);
}
