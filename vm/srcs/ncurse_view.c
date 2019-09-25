/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurse_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:28:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/25 03:25:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cw_ncurse.h"
#include "vm.h"
#include "libft.h"
#include "ft_printf.h"


static int		ncurses_error(char *str, char *progname)
{
	ncurses_end();
	ft_dprintf(2, "%s: ncurse: %s\n", progname, str);
	return (0);
}

/*
** WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
*/

static int		createArenaBox(t_env *e)
{
	int			winx;
	int			winy;

	winx = 64 * 3 + 1;
	winy = 64 + 1;
	if (!(ncu.arenaWinBox = subwin(ncu.mainWin, winy, winx, 0, 0)))
		return (ncurses_error("Failed to init arena Window Box.", e->progname));
	box(ncu.arenaWinBox, 0, 0);
	mvwaddch(ncu.arenaWinBox, 0, (winx * 0.5) - 8, ACS_RTEE);
	wattron(ncu.arenaWinBox, COLOR_PAIR(3));
	mvwaddstr(ncu.arenaWinBox, 0, (winx * 0.5) - 7, " C O R E W A R ");
	wattroff(ncu.arenaWinBox, COLOR_PAIR(3));
	mvwaddch(ncu.arenaWinBox, 0, (winx * 0.5) + 8, ACS_LTEE);
	wrefresh(ncu.arenaWinBox);
	if (!(ncu.arenaWin = subwin(ncu.arenaWinBox, (winy - 2), winx - 2, 1, 1)))
		return (ncurses_error("Failed to init arena Window.", e->progname));
	scrollok(ncu.arenaWin, TRUE);
	return (1);
}

static int		createInfoBox(t_env *e)
{
	int			winx;
	int			winy;

	winx = 60;
	winy = 64 + 1;
	if (!(ncu.infoWinBox = subwin(ncu.mainWin, winy, winx, 0, 0)))
		return (ncurses_error("Failed to init info Window Box.", e->progname));
	box(ncu.infoWinBox, 0, 0);
	mvwaddch(ncu.infoWinBox, 0, (winx * 0.5) - 4, ACS_RTEE);
	wattron(ncu.infoWinBox, COLOR_PAIR(3));
	mvwaddstr(ncu.infoWinBox, 0, (winx * 0.5) - 3, " Info ");
	wattroff(ncu.infoWinBox, COLOR_PAIR(3));
	mvwaddch(ncu.infoWinBox, 0, (winx * 0.5) + 3, ACS_LTEE);
	wrefresh(ncu.infoWinBox);
	if (!(ncu.infoWin = subwin(ncu.infoWinBox, (winy - 2), winx - 2, 1, 1)))
		return (ncurses_error("Failed to init info Window.", e->progname));
	return (1);
}

static int		createInfoLine(t_env *e)
{
	if (!(ncu.infoLine = subwin(ncu.mainWin, 1, COLS, LINES - 1, 0)))
		return (ncurses_error("Failed to init infoLine Window.", e->progname));
	return (1);
}

static void		colors()
{
	start_color();
	use_default_colors();
	init_pair(1, -1, -1); // Default
	init_pair(2, COLOR_CYAN, -1);
	init_pair(3, COLOR_YELLOW, -1);
	init_pair(4, COLOR_RED, -1);
	init_pair(5, COLOR_BLUE, -1);
	init_pair(6, COLOR_MAGENTA, -1);
	init_pair(7, COLOR_GREEN, -1);
	init_pair(8, COLOR_WHITE, COLOR_RED);
}

static int		ncurses_start(t_env *e)
{
	ft_memset(&ncu, 0, sizeof(ncu));
	if ((ncu.mainWin = initscr()) == NULL)
		return (ncurses_error("Failed to init main Window.", e->progname));
	noecho();
	cbreak();
	keypad(ncu.mainWin, TRUE);
	colors();
	return (createArenaBox(e) && createInfoBox(e) && createInfoLine(e));
}

/*
** int delwin(WINDOW *win);
**
** Calling delwin deletes the named window, freeing all memory associated with
** it (it does not actually erase the window's screen image).
** Subwindows must be deleted before the main window can be deleted.
*/

void			ncurses_end()
{
	if (ncu.arenaWin)
		delwin(ncu.arenaWin);
	if (ncu.arenaWinBox)
		delwin(ncu.arenaWinBox);
	if (ncu.infoWin)
		delwin(ncu.infoWin);
	if (ncu.infoWinBox)
		delwin(ncu.infoWinBox);
	if (ncu.infoLine)
		delwin(ncu.infoLine);
	endwin();
	ft_memset(&ncu, 0, sizeof(ncu));
}

int				ncurse_view(t_env *e)
{
	e->pid = fork();
	if (e->pid < 0)
		return (ERR_FORK);
	if (e->pid == 0)
	{
		ft_printf("Starting ncurses...\n");
		if (ncurses_start(e))
		{
			while (1) ;
		}
		ncurses_end();
		exit(0);
	}
	sleep(2);
	return (IS_OK);
}
