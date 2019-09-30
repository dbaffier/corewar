/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:30:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 21:44:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			update_affVMStatus(t_env *e)
{
	char		*status[2];

	status[0] = "RUNNING";
	status[1] = "PAUSED";
	if (e->ncu.winx > 6)
	{
		mvwprintw(e->ncu.vm_win, 0, e->ncu.winx / 2 - 6, "** %s **\n",
		status[e->pause]);
		wclrtoeol(e->ncu.vm_win);
		mvwprintw(e->ncu.vm_win, 1, e->ncu.winx / 2 - 7, "speed: %d/%d\n\n",
		VM_SPEED_LIMIT - e->speed, VM_SPEED_LIMIT);
	}
	else
	{
		wprintw(e->ncu.vm_win, "** %s **\n", status[e->pause]);
		wclrtoeol(e->ncu.vm_win);
		wprintw(e->ncu.vm_win, "speed: %d/%d\n\n",
		VM_SPEED_LIMIT - e->speed, VM_SPEED_LIMIT);
	}
}

void			update_affVMInfo(t_env *e, size_t cycle)
{
	wattron(e->ncu.vm_win, A_BOLD);
	wattron(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wclrtoeol(e->ncu.vm_win);
	update_affVMStatus(e);
	wclrtoeol(e->ncu.vm_win);
	wprintw(e->ncu.vm_win, "Cycle: %d\n\n", cycle);
	wclrtoeol(e->ncu.vm_win);
	wprintw(e->ncu.vm_win, "CYCLE_TO_DIE: %d", e->cycle_to_die);
	wattroff(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wattroff(e->ncu.vm_win, A_BOLD);
	wrefresh(e->ncu.vm_win);
}

void			update_affChampion(t_env *e, t_process *proc)
{
	(void)proc;
	(void)e;
}
