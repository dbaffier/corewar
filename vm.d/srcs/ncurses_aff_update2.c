/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:42:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/19 14:42:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			update_aff_process_pc(t_env *e)
{
	t_process	*proc;

	proc = e->proc;
	if (e->ncu.active)
		while (proc)
		{
			update_aff_arena(*(REG_CAST *)proc->pc, 1,
			(short[2]){0, proc->color[1]}, e);
			proc = proc->next;
		}
}
