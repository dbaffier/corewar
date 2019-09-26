/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_init_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:28:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/26 04:22:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"

/*
** Available colors:
** 	COLOR_BLACK
** 	COLOR_RED
** 	COLOR_GREEN
** 	COLOR_YELLOW
** 	COLOR_BLUE
** 	COLOR_MAGENTA
** 	COLOR_CYAN
** 	COLOR_WHITE
*/

static void		colors(t_env *e)
{
	static short	color_combo[] = {
		COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_RED,
	};
	short			i;
	t_process		*proc;

	i = 2;
	proc = e->proc;
	start_color();
	use_default_colors();
	init_pair(1, -1, -1); // Default
	while (proc)
	{
		proc->color[0] = i;
		init_pair(i, color_combo[i - 2], -1); // Player color
		i++;
		proc->color[1] = i;
		init_pair(i, -1, color_combo[i - 3]); // Player color PC
		i++;
		proc = proc->next;
	}

	// init_pair(2, COLOR_CYAN, -1);
	// init_pair(3, COLOR_YELLOW, -1);
	// init_pair(4, COLOR_RED, -1);
	// init_pair(5, COLOR_BLUE, -1);
	// init_pair(6, COLOR_MAGENTA, -1);
	// init_pair(8, COLOR_WHITE, COLOR_RED);
}

int				ncurses_init(t_env *e)
{
	int			err;

	signal(SIGWINCH, ncurses_resizeWindow);
	if ((e->ncu.mainWin = initscr()) == NULL)
		return (ERR_NCURSE_MAINWIN);
	noecho();
	cbreak();
	keypad(e->ncu.mainWin, TRUE);
	colors(e);
	if (COLS < ARENA_LINE_LEN || LINES < ARENA_COL_LEN)
		return (ncurses_termTooSmall(e));
	if ((err = createArenaBox(e)) == IS_OK)
		if ((err = createInfoBox(e)) == IS_OK)
			err = createInfoLine(e);
	return (err);
}

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
