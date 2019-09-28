/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:54:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/28 19:42:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_ncurse.h"

int		full_len_size(unsigned short reg_nb, t_param *params)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < reg_nb)
	{
		if (params[i].size == 0)
			return (0);
		len += params[i].size;
		i++;
	}
	return (len);
}

void			move_process_pc(t_process *proc, int len, t_env *e)
{
	int			y;
	int			x;

	if (e->ncu.arenaWin)
	{
		wprintw(e->ncu.infoWin, "Player %d moving %d bits forward\n", proc->id, len);
		y = (*(REG_CAST *)proc->pc * 3) / ARENA_LINE_LEN;
		x = (*(REG_CAST *)proc->pc * 3) % ARENA_LINE_LEN;
		wattron(e->ncu.arenaWin, COLOR_PAIR(proc->color[0]));
		mvwprintw(e->ncu.arenaWin, y, x, "%02X",
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc));
		wattroff(e->ncu.arenaWin, COLOR_PAIR(proc->color[0]));
	}
	*(REG_CAST *)proc->pc = (*(REG_CAST *)proc->pc + len) % MEM_SIZE;
	if (e->ncu.arenaWin)
	{
		y = (*(REG_CAST *)proc->pc * 3) / ARENA_LINE_LEN;
		x = (*(REG_CAST *)proc->pc * 3) % ARENA_LINE_LEN;
		wattron(e->ncu.arenaWin, COLOR_PAIR(proc->color[1]));
		mvwprintw(e->ncu.arenaWin, y, x, "%02X",
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc));
		wattroff(e->ncu.arenaWin, COLOR_PAIR(proc->color[1]));
		wrefresh(e->ncu.arenaWin);
	}
}
