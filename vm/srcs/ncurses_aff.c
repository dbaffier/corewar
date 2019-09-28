/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/29 00:05:06 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void		arena_get_color(size_t i[2], char flag[2], t_process **proc,
t_env *e)
{
	if (i[0] >= i[1] && i[0] < i[1] + (*proc)->data_size)
	{
		if (flag[0] == 0)
		{
			wattron(e->ncu.arenaWin, (*(REG_CAST *)(*proc)->pc == i[0]) ?
				COLOR_PAIR((*proc)->color[1]) : COLOR_PAIR((*proc)->color[0]));
			if (*(REG_CAST *)(*proc)->pc != i[0])
				flag[0] = 1;
		}
		if (flag[1] == 0)
			flag[1] = 1;
		return ;
	}
	if (flag[0] == 1)
	{
		wattron(e->ncu.arenaWin, COLOR_PAIR(1));
		flag[0] = 0;
	}
	if (flag[1] == 1)
	{
		*proc = (*proc)->prev;
		i[1] += (MEM_SIZE / e->nb_players);
		flag[1] = 0;
	}
}

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
	t_process	*proc;
	size_t		i[2];
	char		flag[2];

	ft_bzero(i, sizeof(i));
	flag[0] = 0;
	flag[1] = 1;
	proc = e->proc;
	if (!e->arena)
		return ;
	while (proc->next)
		proc = proc->next;
	while (i[0] < MEM_SIZE)
	{
		arena_get_color(i, flag, &proc, e);
		wprintw(e->ncu.arenaWin, "%02X", *((unsigned char *)e->arena + i[0]));
		if (proc && *(REG_CAST *)proc->pc == i[0])
			wattron(e->ncu.arenaWin, COLOR_PAIR(1));
		i[0]++;
		if (i[0] % ARENA_VALUE_PER_LINE != 0)
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
		// mvwprintw(e->ncu.champWin, y, 20, "Player %d\n", proc->id);
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
