/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:54:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/28 01:11:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_ncurse.h"

void			move_process_pc(t_process *proc, int len, t_env *e)
{
	int			y;
	int			x;

	if (e->ncu.arenaWin)
	{
wprintw(e->ncu.infoWin, "Player %d moving %d bits forward\n", proc->id, len);
// wprintw(e->ncu.infoWin, "proc %d move %d from %ld", proc->id, len, *(REG_CAST *)proc->pc);
		y = (*(REG_CAST *)proc->pc * 3) / ARENA_LINE_LEN;
		x = (*(REG_CAST *)proc->pc * 3) % ARENA_LINE_LEN;
// wprintw(e->ncu.infoWin, ", y=%d x=%d", y, x);
		wattron(e->ncu.arenaWin, COLOR_PAIR(proc->color[0]));
		mvwprintw(e->ncu.arenaWin, y, x, "%02X",
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc));
		wattroff(e->ncu.arenaWin, COLOR_PAIR(proc->color[0]));
	}
	*(REG_CAST *)proc->pc = (*(REG_CAST *)proc->pc + len) % MEM_SIZE;
// wprintw(e->ncu.infoWin, ", pc=%d", *(REG_CAST *)proc->pc);
	if (e->ncu.arenaWin)
	{
		y = (*(REG_CAST *)proc->pc * 3) / ARENA_LINE_LEN;
		x = (*(REG_CAST *)proc->pc * 3) % ARENA_LINE_LEN;
// wprintw(e->ncu.infoWin, ", y=%d x=%d\n", y, x);
		wattron(e->ncu.arenaWin, COLOR_PAIR(proc->color[1]));
		mvwprintw(e->ncu.arenaWin, y, x, "%02X",
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc));
		wattroff(e->ncu.arenaWin, COLOR_PAIR(proc->color[1]));
		wrefresh(e->ncu.arenaWin);
	}
}
