/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:38:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/07 20:39:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void		arena_copy(void *arena, int pc, REG_CAST *value, size_t size)
{
	uint8_t		*ptr;
	size_t		offset;
	size_t		i;

	ptr = (uint8_t *)arena;
	i = 0;
	if (!arena || !value || size > REG_SIZE)
		return ;
	offset = calc_mod(pc, MEM_SIZE);
	while (i < size)
	{
		ptr[(offset + i) % MEM_SIZE] = ((uint8_t *)value)[REG_SIZE - 1 - i];
		i++;
	}
}

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
