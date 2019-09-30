/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 23:21:09 by gbourgeo         ###   ########.fr       */
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

static void		ncurses_aff_arena(t_env *e)
{
	size_t		i;
	t_process	*proc;

	i = 0;
	if (!e->ncu.arena_win || !e->arena || !e->colors)
		return ;
	while (i < MEM_SIZE)
	{
		wattron(e->ncu.arena_win, COLOR_PAIR(e->colors[i]));
		if ((proc = e->proc))
			while (proc)
			{
				if (*(REG_CAST *)proc->pc == i)
					wattron(e->ncu.arena_win, COLOR_PAIR(proc->color[1]));
				proc = proc->next;
			}
		wprintw(e->ncu.arena_win, "%02x", *((unsigned char *)e->arena + i));
		wattron(e->ncu.arena_win, COLOR_PAIR(COREWAR_DFLT_COLOR));
		if (++i % ARENA_VALUE_PER_LINE != 0)
			wprintw(e->ncu.arena_win, " ");
	}
	wrefresh(e->ncu.arena_win);
}

/*
** players = 1, y1 = -1
** players = 2, y1 = -2, y2 = 1
** players = 3, y1 = -4, y2 = -1, y3 = 3
** players = 4, y1 = -6, y2 = -3, y3 = 0, y4 = 3
*/

static void		ncurses_aff_champion(t_env *e)
{
	t_process	*proc;
	t_header	*play;
	int			y;

	if (!e->ncu.champ_win)
		return ;
	wclear(e->ncu.champ_win);
	proc = e->proc;
	y = (e->ncu.winy / 2) + (((e->nb_players * 3)) / 2) - 2;
	while (proc)
	{
		if ((play = (t_header *)proc->file))
		{
			wattron(e->ncu.champ_win, COLOR_PAIR(proc->color[1]));
			mvwprintw(e->ncu.champ_win, y, 0, "Player %d", proc->id);
			wattroff(e->ncu.champ_win, COLOR_PAIR(proc->color[1]));
			mvwprintw(e->ncu.champ_win, y + 1, 0, "%s (%s)",
				play->prog_name, play->comment);
			y -= 3;
		}
		proc = proc->next;
	}
	wrefresh(e->ncu.champ_win);
}

static void		ncurses_aff_vminfo(t_env *e)
{
	wattron(e->ncu.vm_win, A_BOLD);
	wattron(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	update_aff_vmstatus(e);
	wprintw(e->ncu.vm_win, "Cycle: 0\n\n");
	wprintw(e->ncu.vm_win, "CYCLE_TO_DIE: %d\n\n", e->cycle_to_die);
	wprintw(e->ncu.vm_win, "CYCLE_DELTA: %d\n\n", CYCLE_DELTA);
	wprintw(e->ncu.vm_win, "NBR_LIVE: %d\n\n", NBR_LIVE);
	wprintw(e->ncu.vm_win, "MAX_CHECKS: %d", MAX_CHECKS);
	wattroff(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wattroff(e->ncu.vm_win, A_BOLD);
	wrefresh(e->ncu.vm_win);
}

void			ncurses_aff_all(t_env *e)
{
	ncurses_aff_arena(e);
	ncurses_aff_champion(e);
	ncurses_aff_vminfo(e);
}
