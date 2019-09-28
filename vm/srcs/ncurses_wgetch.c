/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_wgetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:34:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/28 19:52:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_ncurse.h"

int				ncurses_wgetch(int *pause, WINDOW *infoWin)
{
	int			ch;

	ch = wgetch(infoWin);
	if (ch == ERR)
		return ((*pause) ? ERR : 1);
	if (ch == ' ')
	{
		if (!(*pause = !*pause))
			wtimeout(infoWin, 20);
			// nodelay(infoWin, TRUE);
		else
			wtimeout(infoWin, -1);
			// nodelay(infoWin, FALSE);
		return (1);
	}
	if (ch == 's')
		return (1);
	return (0);
}
