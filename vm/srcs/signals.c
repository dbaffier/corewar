/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:17:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/01 22:48:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		g_env.term_too_small = ncurses_termtoosmall(&g_env);
	else if ((sig = create_arenabox(&g_env)) == IS_OK)
		if ((sig = create_infobox(&g_env)) == IS_OK)
		{
			ncurses_aff_all(&g_env);
			g_env.term_too_small = 0;
			return ;
		}
	ncurses_end(&g_env);
	free_env(&g_env);
	corewar_errors(sig, NULL, &g_env);
	exit(1);
}
