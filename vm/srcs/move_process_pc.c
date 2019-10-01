/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_process_pc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:54:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/01 17:11:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_ncurse.h"

int				full_len_size(unsigned short reg_nb, t_param *params)
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

REG_CAST		calc_mod(int len, size_t size)
{
	while (len < 0)
		len += size;
	return (len % size);
}

void			move_process_pc(t_process *proc, int len, t_env *e)
{
	int			y;
	int			x;

	if (e->ncu.arena_win)
	{
		y = ((*(REG_CAST *)proc->pc * 3) / ARENA_LINE_LEN) % MEM_SIZE;
		x = ((*(REG_CAST *)proc->pc * 3) % ARENA_LINE_LEN) % MEM_SIZE;
		wattron(e->ncu.arena_win, COLOR_PAIR(e->colors[*(REG_CAST *)proc->pc]));
		mvwprintw(e->ncu.arena_win, y, x, "%02x",
		*((unsigned char *)e->arena + *(REG_CAST *)proc->pc));
		wattroff(e->ncu.arena_win, COLOR_PAIR(e->colors[*(REG_CAST *)proc->pc]));
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
