/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:38:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/13 00:46:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static t_bytes	*new_bytes(int offset, int nb_cycles, t_bytes *old)
{
	t_bytes		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (old);
	new->cycle_to_print = nb_cycles + ARENA_COPY_DURATION;
	new->offset = offset;
	new->next = old;
	if (old)
		old->prev = new;
	return (new);
}

void			arena_copy(int offset, REG_CAST *value, short color, t_env *e)
{
	uint8_t		*ptr;
	size_t		off;
	size_t		i;

	ptr = (uint8_t *)e->arena;
	i = 0;
	if (!ptr || !value)
		return ;
	off = calc_mod(offset, MEM_SIZE);
	if (e->ncu.active == TRUE)
		e->bytes = new_bytes(off, e->nb_cycles, e->bytes);
	while (i++ < REG_SIZE)
	{
		ptr[off] = ((uint8_t *)value)[REG_SIZE - i];
		if (e->colors)
			e->colors[off] = color;
		off = (off + 1) % MEM_SIZE;
	}
	update_aff_arena(offset, COREWAR_ARENA_COLOR, e);
}

REG_CAST		arena_get(void *arena, int pc, size_t size)
{
	char		tab[REG_SIZE];
	uint8_t		*data;
	size_t		offset;
	int			i;

	ft_bzero(tab, REG_SIZE);
	data = (uint8_t *)arena;
	i = 0;
	if (size > REG_SIZE)
		return (0);
	offset = calc_mod(pc, MEM_SIZE);
	while (size--)
	{
		tab[size] = data[(offset + i) % MEM_SIZE];
		i++;
	}
	if (i == 1)
		return (*(char *)tab);
	if (i == 2)
		return (*(short *)tab);
	return (*(REG_CAST *)tab);
}
