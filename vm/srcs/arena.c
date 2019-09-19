/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:29:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/19 23:08:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

#include <stdio.h>
int				get_arena(t_env *e)
{
	int			i;

	i = 0;
	if ((e->arena = ft_memalloc(MEM_SIZE)) == NULL)
		return (ERR_MALLOC);
	while (i < e->nb_players)
	{
		printf("%p: copying at %p %d bytes\n", e->arena,
			(void*)((char *)e->arena + (i * (MEM_SIZE / e->nb_players))),
			e->proc[i].data_size);
		ft_memcpy((char *)e->arena + (i * (MEM_SIZE / e->nb_players)),
		(char *)e->proc[i].file + sizeof(t_header),
		e->proc[i].data_size);
		i++;
	}
	return (IS_OK);
}
