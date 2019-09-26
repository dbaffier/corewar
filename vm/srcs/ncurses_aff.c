/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/26 03:47:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			ncurses_affArena(t_env *e)
{
	size_t			i;

	i = 0;
	if (!e->arena)
		return ;
	wcursyncup(e->ncu.arenaWin);
	while (i < MEM_SIZE)
	{
		wprintw(e->ncu.arenaWin, "%02X", *((unsigned char *)e->arena + i));
		i++;
		if (i % ARENA_VALUE_PER_LINE == 0)
			wprintw(e->ncu.arenaWin, "\n");
		else
			wprintw(e->ncu.arenaWin, " ");
	}
	wrefresh(e->ncu.arenaWin);
}

void			ncurses_affInfo(t_env *e)
{
	t_process	*proc;
	t_header	*play;

	if (!(proc = e->proc))
		return ;
	wclear(e->ncu.infoWin);
	wrefresh(e->ncu.infoWin);
	while (proc->next)
		proc = proc->next;
	while (proc)
	{
		play = (t_header *)proc->file;
		wclear(e->ncu.infoWin);
		wprintw(e->ncu.infoWin, "coucou\n");
		// proc->id, proc->data_size, play->prog_name, play->comment);
		proc = proc->prev;
	}
}
