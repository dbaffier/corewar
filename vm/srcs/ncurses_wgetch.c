/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_wgetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:34:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/01 19:54:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_ncurse.h"

static int		ncurses_wgetch_next(int ch, int *speed, int *pause,
WINDOW *info_win)
{
	if (ch == '-')
	{
		if ((*speed += VM_SPEED_RATIO) > VM_SPEED_LIMIT)
			*speed = VM_SPEED_LIMIT;
		if (!*pause)
			wtimeout(info_win, *speed);
		return (!pause);
	}
	return (0);
}

int				ncurses_wgetch(int *speed, int *pause, WINDOW *info_win)
{
	int			ch;

	ch = wgetch(info_win);
	if (ch == ERR)
		return ((*pause) ? ERR : 1);
	if (ch == ' ')
	{
		if (!(*pause = !*pause))
			wtimeout(info_win, *speed);
		else
			wtimeout(info_win, -1);
		return (1);
	}
	if (ch == 's')
		return (1);
	if (ch == '+')
	{
		if ((*speed -= VM_SPEED_RATIO) < 0)
			*speed = 0;
		if (!*pause)
			wtimeout(info_win, *speed);
		return (!pause);
	}
	return (ncurses_wgetch_next(ch, speed, pause, info_win));
}
