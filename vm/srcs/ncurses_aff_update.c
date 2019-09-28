/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:30:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/29 00:18:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			update_affVMInfo(t_env *e, size_t cycle)
{
	wattron(e->ncu.vmWin, A_BOLD);
	wattron(e->ncu.vmWin, COLOR_PAIR(4));
	wclrtoeol(e->ncu.vmWin);
	ncurses_affVMStatus(e);
	wclrtoeol(e->ncu.vmWin);
	wprintw(e->ncu.vmWin, "Cycle: %d\n\n", cycle);
	wclrtoeol(e->ncu.vmWin);
	wprintw(e->ncu.vmWin, "CYCLE_TO_DIE: %d", e->cycle_to_die);
	wattroff(e->ncu.vmWin, A_BOLD);
	wattroff(e->ncu.vmWin, COLOR_PAIR(4));
	wrefresh(e->ncu.vmWin);
}
