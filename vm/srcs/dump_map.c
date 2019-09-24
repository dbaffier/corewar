/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:55:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/24 03:58:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "vm.h"

void			dump_map(unsigned char *arena, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (i % 32 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x", arena[i]);
		i++;
		if (i % 32 == 0)
			ft_printf("\n");
		else
			ft_printf(" ");
	}
}
