/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:20:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/28 21:48:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int				ncurses_termTooSmall(t_env *e)
{
	wbkgd(e->ncu.mainWin, COLOR_PAIR(1));
	wattron(e->ncu.mainWin, A_BOLD);
	wattron(e->ncu.mainWin, COLOR_PAIR(4));
	mvwaddstr(e->ncu.mainWin, (LINES * 0.5) - 1, (COLS * 0.5) - 3, "TERMINAL");
	mvwaddstr(e->ncu.mainWin, (LINES * 0.5), (COLS * 0.5) - 4, "TOO SMALL!");
	wattroff(e->ncu.mainWin, COLOR_PAIR(4));
	wattroff(e->ncu.mainWin, A_BOLD);
	wrefresh(e->ncu.mainWin);
	return (IS_OK);
}

/*
** WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
*/

int				createArenaBox(t_env *e)
{
	int			winx;
	int			winy;

	winx = ARENA_LINE_LEN + 1;
	winy = ARENA_VALUE_PER_LINE + 1;
	if (!(e->ncu.arenaWinBox = subwin(e->ncu.mainWin, winy, winx, 0, 0)))
		return (ERR_NCURSE_ARENABOX);
	box(e->ncu.arenaWinBox, 0, 0);
	mvwaddch(e->ncu.arenaWinBox, 0, (winx * 0.5) - 8, ACS_RTEE);
	wattron(e->ncu.arenaWinBox, COLOR_PAIR(2));
	mvwaddstr(e->ncu.arenaWinBox, 0, (winx * 0.5) - 7, " C O R E W A R ");
	wattroff(e->ncu.arenaWinBox, COLOR_PAIR(2));
	mvwaddch(e->ncu.arenaWinBox, 0, (winx * 0.5) + 8, ACS_LTEE);
	wrefresh(e->ncu.arenaWinBox);
	if (!(e->ncu.arenaWin = subwin(e->ncu.arenaWinBox, winy - 2, winx - 2, 1, 1)))
		return (ERR_NCURSE_ARENAWIN);
	ncurses_affArena(e);
	return (IS_OK);
}

static int		createInfoWin(t_env *e, int winx, int winy)
{
	winy = (winy - 2) / 3;
	e->ncu.winx = winx - 2;
	e->ncu.winy = winy;
	if (!(e->ncu.champWin = subwin(e->ncu.infoWinBox,
	winy, winx - 2, 1, COLS - winx + 1)))
		return (ERR_NCURSE_CHAMPWIN);
	if (!(e->ncu.vmWin = subwin(e->ncu.infoWinBox,
	winy, winx - 2, winy + 1, COLS - winx + 1)))
		return (ERR_NCURSE_VMWIN);
	if (!(e->ncu.infoWin = subwin(e->ncu.infoWinBox,
	winy, winx - 2, winy * 2 + 1, COLS - winx + 1)))
		return (ERR_NCURSE_INFOWIN);
	wbkgd(e->ncu.champWin, COLOR_PAIR(3));
	scrollok(e->ncu.infoWin, TRUE);
	return (IS_OK);
}

int				createInfoBox(t_env *e)
{
	int			winx;
	int			winy;

	winx = COLS - (ARENA_LINE_LEN + 1);
	winy = ARENA_VALUE_PER_LINE + 1;
	if (!(e->ncu.infoWinBox = subwin(e->ncu.mainWin, winy, winx, 0, COLS - winx)))
		return (ERR_NCURSE_INFOBOX);
	box(e->ncu.infoWinBox, 0, 0);
	mvwaddch(e->ncu.infoWinBox, 0, (winx * 0.5) - 4, ACS_RTEE);
	wattron(e->ncu.infoWinBox, COLOR_PAIR(2));
	mvwaddstr(e->ncu.infoWinBox, 0, (winx * 0.5) - 3, " I N F O ");
	wattroff(e->ncu.infoWinBox, COLOR_PAIR(2));
	mvwaddch(e->ncu.infoWinBox, 0, (winx * 0.5) + 6, ACS_LTEE);
	wrefresh(e->ncu.infoWinBox);
	createInfoWin(e, winx, winy);
	ncurses_affChampion(e);
	ncurses_affVMInfo(e);
	return (IS_OK);
}
