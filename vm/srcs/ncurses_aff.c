/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/29 23:06:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

/*
** size_t i[2] :
** i[0] : arena iteration counter
** i[1] : arena color offset
**
** char flag[2] :
** flag[0] : Did we changed the color ?
** flag[1] : Did we changed process ?
*/

void			ncurses_affArena(t_env *e)
{
	size_t		i;
	t_process	*proc;

	i = 0;
	if (!e->ncu.arenaWin || !e->arena || !e->colors)
		return ;
	while (i < MEM_SIZE)
	{
		wattron(e->ncu.arenaWin, COLOR_PAIR(e->colors[i]));
		if ((proc = e->proc))
			while (proc)
			{
				if (*(REG_CAST *)proc->pc == i)
					wattron(e->ncu.arenaWin, COLOR_PAIR(proc->color[1]));
				proc = proc->next;
			}
		wprintw(e->ncu.arenaWin, "%02X", *((unsigned char *)e->arena + i));
		// wprintw(e->ncu.arenaWin, "%02hd", *(e->colors + i));
		wattron(e->ncu.arenaWin, COLOR_PAIR(COREWAR_DFLT_COLOR));
		if (++i % ARENA_VALUE_PER_LINE != 0)
			wprintw(e->ncu.arenaWin, " ");
	}
	wrefresh(e->ncu.arenaWin);
}

void			ncurses_affChampion(t_env *e)
{
	t_process	*proc;
	t_header	*play;
	int			y;

	if (!(proc = e->proc) || !e->ncu.champWin)
		return ;
	y = 0;
	while (proc->next)
		proc = proc->next;
	wclear(e->ncu.champWin);
	while (proc)
	{
		play = (t_header *)proc->file;
		wattron(e->ncu.champWin, COLOR_PAIR(proc->color[1]));
		wprintw(e->ncu.champWin, "Player %d\n", proc->id);
		wattroff(e->ncu.champWin, COLOR_PAIR(proc->color[1]));
		wprintw(e->ncu.champWin, "%s (%s)\n\n\n", play->prog_name, play->comment);
		y += 3;
		proc = proc->prev;
	}
	wrefresh(e->ncu.champWin);
}

void			ncurses_affVMInfo(t_env *e)
{
	wattron(e->ncu.vmWin, A_BOLD);
	wattron(e->ncu.vmWin, COLOR_PAIR(4));
	ncurses_affVMStatus(e);
	wprintw(e->ncu.vmWin, "Cycle: 0\n\n");
	wprintw(e->ncu.vmWin, "CYCLE_TO_DIE: %d\n\n", e->cycle_to_die);
	wprintw(e->ncu.vmWin, "CYCLE_DELTA: %d\n\n", CYCLE_DELTA);
	wprintw(e->ncu.vmWin, "NBR_LIVE: %d\n\n", NBR_LIVE);
	wprintw(e->ncu.vmWin, "MAX_CHECKS: %d", MAX_CHECKS);
	wattroff(e->ncu.vmWin, COLOR_PAIR(4));
	wattroff(e->ncu.vmWin, A_BOLD);
	wrefresh(e->ncu.vmWin);
}

void			ncurses_affVMStatus(t_env *e)
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
