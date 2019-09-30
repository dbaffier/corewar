/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 04:02:57 by gbourgeo         ###   ########.fr       */
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

static void		ncurses_affArena(t_env *e)
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
		wprintw(e->ncu.arenaWin, "%02x", *((unsigned char *)e->arena + i));
		wattron(e->ncu.arenaWin, COLOR_PAIR(COREWAR_DFLT_COLOR));
		if (++i % ARENA_VALUE_PER_LINE != 0)
			wprintw(e->ncu.arenaWin, " ");
	}
	wrefresh(e->ncu.arenaWin);
}

static int		champWin_middle(int winy, int players, int pos)
{
	if ((winy <= players * 3 - 1))
		return (0);
	return ((winy / 2) - (((players * 3) / 2)) * (players - pos - 1));
}

static void		ncurses_affChampion(t_env *e)
{
	t_process	*proc;
	t_header	*play;
	int			y;

	if (!e->ncu.champWin)
		return ;
	wclear(e->ncu.champWin);
	proc = e->proc;
	while (proc)
	{
		if ((play = (t_header *)proc->file))
		{
			y = champWin_middle(e->ncu.winy, e->nb_players, proc->pos);
			wattron(e->ncu.champWin, COLOR_PAIR(proc->color[1]));
			mvwprintw(e->ncu.champWin, y, 0, "Player %d", proc->id);
			wattroff(e->ncu.champWin, COLOR_PAIR(proc->color[1]));
			mvwprintw(e->ncu.champWin, y + 1, 0, "%s (%s)",
				play->prog_name, play->comment);
		}
		proc = proc->next;
	}
	wrefresh(e->ncu.champWin);
}

static void		ncurses_affVMInfo(t_env *e)
{
	wattron(e->ncu.vmWin, A_BOLD);
	wattron(e->ncu.vmWin, COLOR_PAIR(4));
	update_affVMStatus(e);
	wprintw(e->ncu.vmWin, "Cycle: 0\n\n");
	wprintw(e->ncu.vmWin, "CYCLE_TO_DIE: %d\n\n", e->cycle_to_die);
	wprintw(e->ncu.vmWin, "CYCLE_DELTA: %d\n\n", CYCLE_DELTA);
	wprintw(e->ncu.vmWin, "NBR_LIVE: %d\n\n", NBR_LIVE);
	wprintw(e->ncu.vmWin, "MAX_CHECKS: %d", MAX_CHECKS);
	wattroff(e->ncu.vmWin, COLOR_PAIR(4));
	wattroff(e->ncu.vmWin, A_BOLD);
	wrefresh(e->ncu.vmWin);
}

void			ncurses_affAll(t_env *e)
{
	ncurses_affArena(e);
	ncurses_affChampion(e);
	ncurses_affVMInfo(e);
}
