/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:17:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/28 20:44:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void				corewar_end(int sig)
{
	(void)sig;
	ncurses_end(&g_env);
	free_env(&g_env);
	exit(1);
}

void				ncurses_resizeWindow(int sig)
{
	if (sig != SIGWINCH)
		return ;
	endwin();
	refresh();
	clear();
	if (COLS < ARENA_LINE_LEN || LINES < ARENA_COL_LEN)
		ncurses_termTooSmall(&g_env);
	else
	{
		createArenaBox(&g_env);
		createInfoBox(&g_env);
	}
}
