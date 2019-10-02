/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:38:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/02 17:07:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			arena_copy(void *dst, void *arena, REG_CAST *value, size_t size)
{
	int8_t		*ptr;
	size_t		i;
	size_t		j;

	ptr = (int8_t *)dst;
	i = 0;
	j = 0;
	while (size--)
	{
		if (ptr + i - (int8_t *)arena >= MEM_SIZE)
		{
			ptr = (int8_t *)arena;
			i = 0;
		}
		*(ptr + i) = ((int8_t *)value)[j++];
		i++;
	}
}

REG_CAST		arena_get(void *dst, void *arena, size_t size)
{
	int8_t		get[REG_SIZE];
	int8_t		*ptr;
	size_t		i;
	size_t		j;

	ptr = (int8_t *)dst;
	i = 0;
	j = 0;
	while (size--)
	{
		if (ptr + i - (int8_t *)arena >= MEM_SIZE)
		{
			ptr = (int8_t *)arena;
			i = 0;
		}
		*(ptr + i) = get[j++];
		i++;
	}
	return (*(REG_CAST *)get);
}
