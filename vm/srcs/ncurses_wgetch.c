/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_wgetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:34:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/09 14:38:57 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_ncurse.h"
#include "libft.h"

static int		ncurses_wgetch_next(int ch, int *speed, int *pause,
WINDOW *win)
{
	if (ch == '-')
	{
		if ((*speed += VM_SPEED_RATIO) > VM_SPEED_LIMIT)
			*speed = VM_SPEED_LIMIT;
		if (!*pause)
			wtimeout(win, *speed);
		return (!pause);
	}
	return (0);
}

int				ncurses_wgetch(int *speed, int *pause, WINDOW *win)
{
	int			ch;

	ch = wgetch(win);
	if (ch == ERR)
		return ((*pause) ? ERR : 1);
	if (ch == ' ')
	{
		if (!(*pause = !*pause))
			wtimeout(win, *speed);
		else
			wtimeout(win, -1);
		return (1);
	}
	if (ch == 's')
		return (1);
	if (ch == '+')
	{
		if ((*speed -= VM_SPEED_RATIO) < 0)
			*speed = 0;
		if (!*pause)
			wtimeout(win, *speed);
		return (!pause);
	}
	return (ncurses_wgetch_next(ch, speed, pause, win));
}

int				ncurses_player_calc_x(int id)
{
	char		*nb;
	int			ret;

	if (!(nb = ft_itoa(id)))
		return (100);
	ret = ft_strlen(nb);
	free(nb);
	return (ret);
}
