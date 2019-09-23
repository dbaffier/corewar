/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:29:53 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 03:13:13 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		print_magic(t_data *data)
{
		clear();
		wattron(data->main_win, COLOR_PAIR(1));
		mvwprintw(data->main_win, 3, 2, "magic number");
		wattroff(data->main_win, COLOR_PAIR(1));
		mvwprintw(data->main_win, 4, 4, "ea 83 f3");
		wrefresh(data->main_win);
		data->print_cursor = 15;
		wait_or_enter(data, 2);
}

void		write_magic(t_data *data)
{
	int		magic;

	magic = 0xf383ea;
	lseek(data->fd, 1, SEEK_SET);
	write(data->fd, &magic, 3);
	if (data->flag & FLAG_N)
		print_magic(data);
}
