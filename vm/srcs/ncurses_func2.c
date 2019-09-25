/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/25 17:02:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#include "ft_printf.h"
void				ncurses_affArena(t_env *e)
{
	size_t			i;

	i = 0;
	if (!e->arena)
		return ;
	wcursyncup(e->ncu.arenaWin);
	while (i < MEM_SIZE)
	{
		wprintw(e->ncu.arenaWin, "%02X", (unsigned char *)e->arena + i);
		i++;
		if (i % ARENA_VALUE_PER_LINE == 0)
			wprintw(e->ncu.arenaWin, "\n");
		else
			wprintw(e->ncu.arenaWin, " ");
	}
	wrefresh(e->ncu.arenaWin);
}
