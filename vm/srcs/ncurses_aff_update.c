/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:30:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/01 19:46:36 by gbourgeo         ###   ########.fr       */
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

void			update_aff_champion(t_env *e, t_process *proc)
{
	(void)proc;
	(void)e;
}

static uint8_t	*calc_arena(unsigned char *arena, unsigned char *e_arena)
{
	if (arena >= e_arena + MEM_SIZE)
		return (e_arena);
	return (arena);
}

void			update_aff_arena_swap(char *arena, size_t size, short color,
t_env *e)
{
	size_t		pos;
	size_t		i;
	int			x;
	int			y;

	i = 0;
	while (size--)
	{
		pos = calc_mod(arena - (char *)e->arena + size, MEM_SIZE);
		y = ((pos * 3) / ARENA_LINE_LEN) % MEM_SIZE;
		x = ((pos * 3) % ARENA_LINE_LEN) % MEM_SIZE;
		e->colors[pos] = color;
		mvwprintw(e->ncu.arena_win, y, x, "%02x",
		*calc_arena((unsigned char *)arena + i, e->arena));
		i++;
	}
}
