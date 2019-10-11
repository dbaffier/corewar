/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:38:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/11 23:59:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void	update_aff_arena(int offset, int size, short color, t_env *e)
{
	size_t	off;
	int		x;
	int		y;

	if (e->ncu.arena_win)
	{
		wattron(e->ncu.arena_win, COLOR_PAIR(COREWAR_ARENA_COLOR));
		while (size--)
		{
			off = calc_mod(offset, MEM_SIZE);
			y = ((off * 3) / ARENA_LINE_LEN) % MEM_SIZE;
			x = ((off * 3) % ARENA_LINE_LEN) % MEM_SIZE;
			e->colors[off] = color;
			mvwprintw(e->ncu.arena_win, y, x, "%02x",
				*((uint8_t *)e->arena + off));
			offset++;
		}
		wattroff(e->ncu.arena_win, COLOR_PAIR(COREWAR_ARENA_COLOR));
	}
}

void		arena_copy(int offset, REG_CAST *value, short color, t_env *e)
{
	uint8_t		*ptr;
	size_t		off;
	size_t		i;

	ptr = (uint8_t *)e->arena;
	i = 0;
	if (!ptr || !value)
		return ;
	off = calc_mod(offset, MEM_SIZE);
	while (i < REG_SIZE)
	{
		ptr[(off + i) % MEM_SIZE] = ((uint8_t *)value)[REG_SIZE - 1 - i];
		i++;
	}
	update_aff_arena(offset, REG_SIZE, color, e);
}

// void		arena_copy(void *arena, int pc, REG_CAST *value, size_t size)
// {
// 	uint8_t		*ptr;
// 	size_t		offset;
// 	size_t		i;

// 	ptr = (uint8_t *)arena;
// 	i = 0;
// 	if (!arena || !value || size > REG_SIZE)
// 		return ;
// 	offset = calc_mod(pc, MEM_SIZE);
// 	while (i < size)
// 	{
// 		ptr[(offset + i) % MEM_SIZE] = ((uint8_t *)value)[REG_SIZE - 1 - i];
// 		i++;
// 	}
// }

REG_CAST	arena_get(void *arena, int pc, size_t size)
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

void		color_copy(short *colors, int pc, short color, size_t size)
{
	size_t		offset;
	size_t		i;

	i = 0;
	if (!colors || size > REG_SIZE)
		return ;
	offset = calc_mod(pc, MEM_SIZE);
	while (i < size)
	{
		colors[(offset + i) % MEM_SIZE] = color;
		i++;
	}
}
