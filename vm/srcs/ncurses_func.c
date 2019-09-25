/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:20:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/25 16:43:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

/*
** int delwin(WINDOW *win);
**
** Calling delwin deletes the named window, freeing all memory associated with
** it (it does not actually erase the window's screen image).
** Subwindows must be deleted before the main window can be deleted.
*/

void			ncurses_end(t_env *e)
{
	if (e->ncu.arenaWin)
		delwin(e->ncu.arenaWin);
	if (e->ncu.arenaWinBox)
		delwin(e->ncu.arenaWinBox);
	if (e->ncu.infoWin)
		delwin(e->ncu.infoWin);
	if (e->ncu.infoWinBox)
		delwin(e->ncu.infoWinBox);
	if (e->ncu.infoLine)
		delwin(e->ncu.infoLine);
	endwin();
	ft_memset(&e->ncu, 0, sizeof(e->ncu));
}

int				ncurses_termTooSmall(t_env *e)
{
	wbkgd(e->ncu.mainWin, COLOR_PAIR(8));
	wattron(e->ncu.mainWin, A_BOLD);
	mvwaddstr(e->ncu.mainWin, (LINES * 0.5) - 1, (COLS * 0.5) - 3, "TERMINAL");
	mvwaddstr(e->ncu.mainWin, (LINES * 0.5), (COLS * 0.5) - 4, "TOO SMALL!");
	wattroff(e->ncu.mainWin, A_BOLD);
	wrefresh(e->ncu.mainWin);
	wbkgd(e->ncu.mainWin, COLOR_PAIR(1));
	return (1);
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
		return (ncurses_error("Failed to init arena Window Box.", e));
	box(e->ncu.arenaWinBox, 0, 0);
	mvwaddch(e->ncu.arenaWinBox, 0, (winx * 0.5) - 8, ACS_RTEE);
	wattron(e->ncu.arenaWinBox, COLOR_PAIR(3));
	mvwaddstr(e->ncu.arenaWinBox, 0, (winx * 0.5) - 7, " C O R E W A R ");
	wattroff(e->ncu.arenaWinBox, COLOR_PAIR(3));
	mvwaddch(e->ncu.arenaWinBox, 0, (winx * 0.5) + 8, ACS_LTEE);
	wrefresh(e->ncu.arenaWinBox);
	if (!(e->ncu.arenaWin = subwin(e->ncu.arenaWinBox, winy - 2, winx - 2, 1, 1)))
		return (ncurses_error("Failed to init arena Window.", e));
	// scrollok(e->ncu.arenaWin, TRUE);
	return (1);
}

int				createInfoBox(t_env *e)
{
	int			winx;
	int			winy;

	winx = COLS - (ARENA_LINE_LEN + 1);
	winy = ARENA_VALUE_PER_LINE + 1;
	if (!(e->ncu.infoWinBox = subwin(e->ncu.mainWin, winy, winx, 0, COLS - winx)))
		return (ncurses_error("Failed to init info Window Box.", e));
	box(e->ncu.infoWinBox, 0, 0);
	mvwaddch(e->ncu.infoWinBox, 0, (winx * 0.5) - 4, ACS_RTEE);
	wattron(e->ncu.infoWinBox, COLOR_PAIR(3));
	mvwaddstr(e->ncu.infoWinBox, 0, (winx * 0.5) - 3, " Info ");
	wattroff(e->ncu.infoWinBox, COLOR_PAIR(3));
	mvwaddch(e->ncu.infoWinBox, 0, (winx * 0.5) + 3, ACS_LTEE);
	wrefresh(e->ncu.infoWinBox);
	if (!(e->ncu.infoWin = subwin(e->ncu.infoWinBox, winy - 2, winx - 2, 1, COLS - winx)))
		return (ncurses_error("Failed to init info Window.", e));
	return (1);
}

int				createInfoLine(t_env *e)
{
	e->ncu.infoLine = subwin(e->ncu.mainWin, 1, COLS, ARENA_COL_LEN + 1, 0);
	if (!e->ncu.infoLine)
		return (ncurses_error("Failed to init infoLine Window.", e));
	return (1);
}
