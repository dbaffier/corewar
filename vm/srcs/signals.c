/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:17:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 23:25:43 by gbourgeo         ###   ########.fr       */
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

void				ncurses_resizewindow(int sig)
{
	if (sig != SIGWINCH)
		return ;
	endwin();
	refresh();
	clear();
	if (COLS < ARENA_LINE_LEN || LINES < ARENA_COL_LEN)
		ncurses_termtoosmall(&g_env);
	else if ((sig = create_arenabox(&g_env)) || (sig = create_infobox(&g_env)))
	{
		ncurses_end(&g_env);
		free_env(&g_env);
		corewar_errors(sig, NULL, &g_env);
		exit(1);
	}
	ncurses_aff_all(&g_env);
}
