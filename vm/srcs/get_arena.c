/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:02:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/23 21:02:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int				get_arena(t_env *e)
{
	int			i;
	t_process	*proc;
	size_t		pc;

	i = e->nb_players - 1;
	proc = e->proc;
	if ((e->arena = ft_memalloc(MEM_SIZE)) == NULL)
		return (corewar_errors(ERR_MALLOC, NULL, e));
	while (proc)
	{
		pc = i * (MEM_SIZE / e->nb_players);
		ft_memcpy(proc->pc, &pc, REG_SIZE);
		ft_memcpy(proc->reg[0], &proc->id, REG_SIZE);
		ft_memcpy((char *)e->arena + pc,
			(char *)proc->file + sizeof(t_header), proc->data_size);
		proc = proc->next;
		i--;
	}
	return (IS_OK);
}
