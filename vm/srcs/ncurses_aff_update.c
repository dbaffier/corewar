/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:30:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/05 18:25:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			update_aff_vmstatus(t_env *e)
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

void			update_aff_vminfo(t_env *e, size_t cycle)
{
	wattron(e->ncu.vm_win, A_BOLD);
	wattron(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wclrtoeol(e->ncu.vm_win);
	update_aff_vmstatus(e);
	wclrtoeol(e->ncu.vm_win);
	wprintw(e->ncu.vm_win, "Cycle: %d\n\n", cycle);
	wclrtoeol(e->ncu.vm_win);
	wprintw(e->ncu.vm_win, "CYCLE_TO_DIE: %d", e->cycle_to_die);
	wattroff(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wattroff(e->ncu.vm_win, A_BOLD);
	wrefresh(e->ncu.vm_win);
}

void			update_aff_champion_dead(t_env *e, t_process *proc)
{
	int			y;
	int			x;

	if (e->ncu.arena_win)
	{
		y = ((*(REG_CAST *)proc->pc * 3) / ARENA_LINE_LEN) % MEM_SIZE;
		x = ((*(REG_CAST *)proc->pc * 3) % ARENA_LINE_LEN) % MEM_SIZE;
		wattron(e->ncu.arena_win,
			COLOR_PAIR(e->colors[*(REG_CAST *)proc->pc]));
		mvwprintw(e->ncu.arena_win, y, x, "%02x",
		*((unsigned char *)e->arena + *(REG_CAST *)proc->pc));
		wattroff(e->ncu.arena_win,
			COLOR_PAIR(e->colors[*(REG_CAST *)proc->pc]));
	}
}

static uint8_t	*calc_arena(unsigned char *arena, unsigned char *e_arena)
{
	if (arena >= e_arena + MEM_SIZE)
		return (e_arena);
	return (arena);
}

void			update_aff_arena(size_t addr, size_t size, short color,
t_env *e)
{
	size_t		pos;
	int			x;
	int			y;

	if (e->ncu.arena_win)
		while (size--)
		{
			pos = calc_mod(addr, MEM_SIZE);
			y = ((pos * 3) / ARENA_LINE_LEN) % MEM_SIZE;
			x = ((pos * 3) % ARENA_LINE_LEN) % MEM_SIZE;
			e->colors[pos] = color;
			mvwprintw(e->ncu.arena_win, y, x, "%02x",
			*calc_arena((uint8_t *)e->arena + pos, e->arena));
			addr++;
		}
}
