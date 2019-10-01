/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:38:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/01 18:50:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			arena_copy(void *dst, void *arena, REG_CAST *value, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			j;

	ptr = (unsigned char *)dst;
	i = 0;
	j = 0;
	while (size--)
	{
		if (ptr + i - (unsigned char *)arena >= MEM_SIZE)
		{
			ptr = (unsigned char *)arena;
			i = 0;
		}
		*(ptr + i) = ((unsigned char *)value)[j++];
		i++;
	}
}
