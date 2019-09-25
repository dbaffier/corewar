/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurse_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 23:28:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/25 17:01:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

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
	ft_memset(&e->ncu, 0, sizeof(e->ncu));
	if ((e->ncu.mainWin = initscr()) == NULL)
		return (ncurses_error("Failed to init main Window.", e));
	noecho();
	cbreak();
	keypad(e->ncu.mainWin, TRUE);
	colors();
	if (COLS < ARENA_LINE_LEN || LINES < ARENA_COL_LEN)
		return (ncurses_termTooSmall(e));
	return (createArenaBox(e) && createInfoBox(e) && createInfoLine(e));
}

int				ncurse_view(t_env *e)
{
	e->pid = fork();
	if (e->pid < 0)
		return (ERR_FORK);
	if (e->pid == 0)
	{
		ft_printf("Starting ncurses...\n");
		signal(SIGWINCH, ncurses_resizeWindow);
		if (ncurses_start(e))
		{
			while (1)
			{
				ncurses_affArena(&g_env);
			}
		}
		ncurses_end(e);
		exit(0);
	}
	sleep(2);
	return (IS_OK);
}
