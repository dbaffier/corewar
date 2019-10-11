/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_process_pc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:54:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/09 19:18:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_ncurse.h"

REG_CAST		calc_mod(int addr, size_t mod)
{
	while (addr < 0)
		addr += mod;
	return (addr % mod);
}

void			move_process_pc(t_process *proc, int len, t_env *e)
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
	*(REG_CAST *)proc->pc = calc_mod(*(REG_CAST *)proc->pc + len, MEM_SIZE);
	if (e->ncu.arena_win)
	{
		y = ((*(REG_CAST *)proc->pc * 3) / ARENA_LINE_LEN) % MEM_SIZE;
		x = ((*(REG_CAST *)proc->pc * 3) % ARENA_LINE_LEN) % MEM_SIZE;
		wattron(e->ncu.arena_win, COLOR_PAIR(proc->color[1]));
		mvwprintw(e->ncu.arena_win, y, x, "%02x",
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc));
		wattroff(e->ncu.arena_win, COLOR_PAIR(proc->color[1]));
		wrefresh(e->ncu.arena_win);
	}
}