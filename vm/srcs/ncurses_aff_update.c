/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:30:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/29 23:11:20 by gbourgeo         ###   ########.fr       */
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
		mvwprintw(e->ncu.vmWin, 0, e->ncu.winx / 2 - 6, "** %s **\n",
		status[e->pause]);
		wclrtoeol(e->ncu.vmWin);
		mvwprintw(e->ncu.vmWin, 1, e->ncu.winx / 2 - 7, "speed: %d/%d\n\n",
		VM_SPEED_LIMIT - e->speed, VM_SPEED_LIMIT);
	}
	else
	{
		wprintw(e->ncu.vmWin, "** %s **\n", status[e->pause]);
		wclrtoeol(e->ncu.vmWin);
		wprintw(e->ncu.vmWin, "speed: %d/%d\n\n",
		VM_SPEED_LIMIT - e->speed, VM_SPEED_LIMIT);
	}
}

void			update_affVMInfo(t_env *e, size_t cycle)
{
	wattron(e->ncu.vmWin, A_BOLD);
	wattron(e->ncu.vmWin, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wclrtoeol(e->ncu.vmWin);
	update_affVMStatus(e);
	wclrtoeol(e->ncu.vmWin);
	wprintw(e->ncu.vmWin, "Cycle: %d\n\n", cycle);
	wclrtoeol(e->ncu.vmWin);
	wprintw(e->ncu.vmWin, "CYCLE_TO_DIE: %d", e->cycle_to_die);
	wattroff(e->ncu.vmWin, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wattroff(e->ncu.vmWin, A_BOLD);
	wrefresh(e->ncu.vmWin);
}
