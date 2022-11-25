/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereverd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:19:59 by jereverd          #+#    #+#             */
/*   Updated: 2022/11/25 18:20:01 by jereverd         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_alloc(size_t size, t_arena *arena)
{
	if (!arena)
		return (malloc(size));
	else
		return (ft_arena_alloc(arena, size));
}
