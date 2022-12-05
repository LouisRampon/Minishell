/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_storage_pool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorampon <lorampon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:44 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/30 15:03:56 by lorampon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_arena(t_shell *sh, size_t size)
{
	sh->arena = malloc(sizeof(t_arena));
	if (sh->arena) {
		sh->arena->cursor = 0;
		sh->arena->size = size;
		sh->arena->data = malloc(sh->arena->size);
		sh->arena->next = 0;
	}
	if (!sh->arena || !sh->arena->data)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

void	ft_free_arena(t_arena *arena)
{
	t_arena *current;
	t_arena *next;

	current = arena;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
}

static int	ft_arena_realloc(t_arena *arena, size_t size)
{
	size_t new_size;
	t_arena *new_node;

	if (size + arena->size > arena->size * 2)
		new_size = size + arena->size * 2;
	else
		new_size = arena->size * 2;
	new_node = malloc(sizeof(t_arena));
	if (new_node) {
		new_node->data = malloc(new_size);
	}
	if (new_node && new_node->data)
	{
		arena->next = new_node;
		new_node->size = new_size;
		new_node->cursor = 0;
		new_node->next = NULL;
		return (1);
	}
	else
		return (0);//todo error
}

void 	*ft_arena_alloc(t_arena *arena, size_t size)
{
	size_t temp;

	while (arena->next && arena->cursor + size > arena->size) {
		arena = arena->next;
	}
	if (arena->cursor + size > arena->size)
		if (ft_arena_realloc(arena, size))
			arena = arena->next;
	temp = arena->cursor;
	arena->cursor += size;
	return (arena->data + temp);
}
