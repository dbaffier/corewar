/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:20:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/07 20:57:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int				ncurses_termtoosmall(t_env *e)
{
	wbkgd(e->ncu.main_win, COLOR_PAIR(COREWAR_DFLT_COLOR));
	wattron(e->ncu.main_win, A_BOLD);
	wattron(e->ncu.main_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	mvwaddstr(e->ncu.main_win, (LINES * 0.5) - 1, (COLS * 0.5) - 3, "TERM");
	mvwaddstr(e->ncu.main_win, (LINES * 0.5), (COLS * 0.5) - 4, "TOO SMALL!");
	wattroff(e->ncu.main_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wattroff(e->ncu.main_win, A_BOLD);
	wrefresh(e->ncu.main_win);
	return (1);
}

/*
** WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int beg_y, int beg_x);
*/

int				create_arenabox(t_env *e)
{
	int			winx;
	int			winy;

	winx = ARENA_LINE_LEN + 1;
	winy = ARENA_VALUE_PER_LINE + 2;
	if (!(e->ncu.arena_winbox = subwin(e->ncu.main_win, winy, winx, 0, 0)))
		return (ERR_NCURSE_ARENABOX);
	box(e->ncu.arena_winbox, 0, 0);
	mvwaddch(e->ncu.arena_winbox, 0, (winx * 0.5) - 8, ACS_RTEE);
	wattron(e->ncu.arena_winbox, COLOR_PAIR(2));
	mvwaddstr(e->ncu.arena_winbox, 0, (winx * 0.5) - 7, " C O R E W A R ");
	wattroff(e->ncu.arena_winbox, COLOR_PAIR(2));
	mvwaddch(e->ncu.arena_winbox, 0, (winx * 0.5) + 8, ACS_LTEE);
	wrefresh(e->ncu.arena_winbox);
	e->ncu.arena_win = subwin(e->ncu.arena_winbox, winy - 2, winx - 2, 1, 1);
	if (!e->ncu.arena_win)
		return (ERR_NCURSE_ARENAWIN);
	return (IS_OK);
}

static int		create_infowin(t_env *e, int winx, int winy)
{
	winy = (winy - 2) / 3;
	e->ncu.winx = winx - 2;
	e->ncu.winy = winy;
	if (!(e->ncu.champ_win = subwin(e->ncu.info_winbox,
	winy, winx - 2, 1, COLS - winx + 1)))
		return (ERR_NCURSE_CHAMPWIN);
	wbkgd(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPWIN_COLOR));
	if (!(e->ncu.vm_win = subwin(e->ncu.info_winbox,
	winy, winx - 2, winy + 1, COLS - winx + 1)))
		return (ERR_NCURSE_VMWIN);
	if (!(e->ncu.info_win = subwin(e->ncu.info_winbox,
	winy + 1, winx - 2, winy * 2 + 1, COLS - winx + 1)))
		return (ERR_NCURSE_INFOWIN);
	wbkgd(e->ncu.info_win, COLOR_PAIR(COREWAR_INFOWIN_COLOR));
	scrollok(e->ncu.info_win, TRUE);
	return (IS_OK);
}

int				create_infobox(t_env *e)
{
	int			winx;
	int			winy;

	winx = COLS - (ARENA_LINE_LEN + 1);
	winy = ARENA_VALUE_PER_LINE + 2;
	e->ncu.info_winbox = subwin(e->ncu.main_win, winy, winx, 0, COLS - winx);
	if (!e->ncu.info_winbox)
		return (ERR_NCURSE_INFOBOX);
	box(e->ncu.info_winbox, 0, 0);
	mvwaddch(e->ncu.info_winbox, 0, (winx * 0.5) - 4, ACS_RTEE);
	wattron(e->ncu.info_winbox, COLOR_PAIR(2));
	mvwaddstr(e->ncu.info_winbox, 0, (winx * 0.5) - 3, " I N F O ");
	wattroff(e->ncu.info_winbox, COLOR_PAIR(2));
	mvwaddch(e->ncu.info_winbox, 0, (winx * 0.5) + 6, ACS_LTEE);
	wrefresh(e->ncu.info_winbox);
	create_infowin(e, winx, winy);
	return (IS_OK);
}
