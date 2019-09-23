/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:35:20 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 02:38:13 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		print_name(t_data *data)
{
		wattron(data->main_win, COLOR_PAIR(2));
		mvwprintw(data->main_win, 3, data->print_cursor + 1, ".name");
		wattroff(data->main_win, COLOR_PAIR(2));
		wrefresh(data->main_win);
		data->print_cursor = data->print_cursor + 5 + 1;
		wait_or_enter(data, 10);
}

static void		write_name(t_data *data)
{
	int		i;

	i = 0;
	if (data->flag & FLAG_N)
		print_name(data);
	while (data->name && data->name[i])
	{
		write(data->fd, &data->name[i++], 1);
	}
	lseek(data->fd, 135 + PADDING, SEEK_SET);
	write(data->fd, &data->size, 1);
}

static void		write_comment(t_data *data)
{
	int		i;

	i = 0;
	while (data->comment && data->comment[i])
		write(data->fd, &data->comment[i++], 1);
	lseek(data->fd, 2192, SEEK_SET);
	data->pc = 2191;
}

void			write_header(t_data *data, int type)
{
	if (type == NAME)
		write_name(data);
	if (type == COMMENT)
		write_comment(data);
}
