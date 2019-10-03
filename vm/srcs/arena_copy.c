/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:38:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/02 20:56:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void			arena_copy(void *arena, REG_CAST pc, REG_CAST *value, size_t size)
{
	uint8_t		*ptr;
	size_t		i;

	ptr = (uint8_t *)arena;
	i = 0;
	while (i < size)
	{
		ptr[(pc + i) % MEM_SIZE] = ((uint8_t *)value)[i];
		i++;
	}
}

REG_CAST		arena_get(void *arena, REG_CAST pc, size_t size)
{
	char		tab[REG_SIZE];
	uint8_t		*data;
	int			i;

	ft_bzero(tab, REG_SIZE);
	data = (uint8_t *)arena;
	i = 0;
	if (size > REG_SIZE)
		return (0);
	while (size--)
	{
		tab[size] = data[(pc + i) % MEM_SIZE];
		i++;
	}
	return (*(REG_CAST *)tab);
}
