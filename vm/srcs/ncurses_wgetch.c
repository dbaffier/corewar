/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_wgetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:34:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/29 00:18:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_ncurse.h"

int				ncurses_wgetch(int *speed, int *pause, WINDOW *infoWin)
{
	int			ch;

	ch = wgetch(infoWin);
	if (ch == ERR)
		return ((*pause) ? ERR : 1);
	if (ch == ' ')
	{
		if (!(*pause = !*pause))
			wtimeout(infoWin, *speed);
		else
			wtimeout(infoWin, -1);
		return (1);
	}
	if (ch == 's')
		return (1);
	if (ch == '+')
	{
		if ((*speed -= VM_SPEED_RATIO) < 0)
			*speed = 0;
		if (!*pause)
			wtimeout(infoWin, *speed);
		return (!pause);
	}
	if (ch == '-')
	{
		if ((*speed += VM_SPEED_RATIO) > VM_SPEED_LIMIT)
			*speed = VM_SPEED_LIMIT;
		if (!*pause)
			wtimeout(infoWin, *speed);
		return (!pause);
	}
	return (0);
}
