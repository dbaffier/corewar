/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:29:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/21 00:56:04 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int				get_arena(t_env *e)
{
	int			i;
	size_t		pc;

	i = 0;
	if ((e->arena = ft_memalloc(MEM_SIZE)) == NULL)
		return (ERR_MALLOC);
	while (i < e->nb_players)
	{
		pc = i * (MEM_SIZE / e->nb_players);
		ft_memcpy(e->proc[i].pc, (unsigned char *)&pc, sizeof(e->proc[i].pc));
		ft_memcpy(e->proc[i].reg[0], &e->proc[i].id, REG_SIZE);
		ft_memcpy((char *)e->arena + pc,
		(char *)e->proc[i].file + sizeof(t_header), e->proc[i].data_size);
		i++;
	}
	return (IS_OK);
}
