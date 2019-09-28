/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_wgetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:34:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/28 17:58:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_ncurse.h"

int				ncurses_wgetch(WINDOW *infoWin)
{
	static int	pause = 0;
	int			ch;

	ch = wgetch(infoWin);
	if (ch == ERR)
		return (ch);
	if (ch == ' ')
	{
		if ((pause = !pause))
			nodelay(infoWin, TRUE);
		else
			nodelay(infoWin, FALSE);
		return (1);
	}
	if (ch == 's')
		return (1);
	return (0);
}
