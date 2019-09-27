/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/26 20:11:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include <stdlib.h>
void			ncurses_affArena(t_env *e)
{
	t_process	*proc;
	size_t		i;
	size_t		off;
	char		flag[2];

	i = 0;
	off = 0;
	flag[0] = 0;
	flag[1] = 1;
	proc = e->proc;
	if (!e->arena)
		return ;
	wcursyncup(e->ncu.arenaWin);
	// wclear(e->ncu.arenaWin);
	// wrefresh(e->ncu.arenaWin);
	while (i < MEM_SIZE)
	{
		// if (proc)
		// {
			if (i >= off && i < off + proc->data_size)
			{
				wcursyncup(e->ncu.infoWin);
				wprintw(e->ncu.infoWin, "%x %d\n", *((unsigned char *)e->arena + i), i);
				wrefresh(e->ncu.infoWin);
				if (flag[0] == 0)
				{
					wattroff(e->ncu.arenaWin, COLOR_PAIR(proc->color[0]));
					flag[0] =1;
				}
				if (flag[1] == 0)
					flag[1] = 1;
			}
			else
			{
				if (flag[0] == 1)
				{
					wattroff(e->ncu.arenaWin, COLOR_PAIR(1));
					flag[0] = 0;
				}
				if (flag[1] == 1)
				{
					proc = proc->next;
					off += (MEM_SIZE / e->nb_players);
					flag[1] = 0;
				}
			}
		// }
		wprintw(e->ncu.arenaWin, "%02X", *((unsigned char *)e->arena + i));
		i++;
		if (i % ARENA_VALUE_PER_LINE != 0)
			wprintw(e->ncu.arenaWin, " ");
	}
	wrefresh(e->ncu.arenaWin);
}

// void			ncurses_affChampionPC(t_env *e)
// {
// 	size_t			i;

// 	i = 0;
// 	if (!e->arena)
// 		return ;
// 	wcursyncup(e->ncu.arenaWin);
// 	while (i < MEM_SIZE)
// 	{
// 		wprintw(e->ncu.arenaWin, "%02X", *((unsigned char *)e->arena + i));
// 		i++;
// 		if (i % ARENA_VALUE_PER_LINE != 0)
// 			wprintw(e->ncu.arenaWin, " ");
// 	}
// 	wrefresh(e->ncu.arenaWin);
// }

void			ncurses_affInfo(t_env *e)
{
	t_process	*proc;
	t_header	*play;

	if (!(proc = e->proc))
		return ;
	wclear(e->ncu.infoWin);
	while (proc->next)
		proc = proc->next;
	while (proc)
	{
		play = (t_header *)proc->file;
		wprintw(e->ncu.infoWin, "Player %d: %s (%s)\n\n",
			proc->id, play->prog_name, play->comment);
		proc = proc->prev;
	}
	wrefresh(e->ncu.infoWin);
}
