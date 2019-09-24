/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 00:42:45 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 01:57:57 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void			starting_color(t_data *data)
{
	//attron(COLOR_PAIR(1));
	/*if ((data->y == 3 && data->x >= 14) || data->y > 3)
	{
		//wattron(data->main_win, COLOR_PAIR(2));
	//	wrefresh(data->main_win);
	}*/
}

void			ending_color(t_data *data)
{
	if (data->y > 5)
	{
		wattroff(data->main_win, COLOR_PAIR(1));
		wattroff(data->main_win, COLOR_PAIR(2));
	}
	wrefresh(data->main_win);
}

void			print_zero(t_data *data)
{
	mvwprintw(data->main_win, data->y, data->x + 1, "0");
	wrefresh(data->main_win);
	data->x = data->x + 1;
}

void			print_buff(t_data *data)
{
	int i;

	i = 0;
	while (data->buffer[i] || i < 16)
	{
		starting_color(data);
		//ending_color(data);
		if (i % 8 == 0)
		{
			mvwprintw(data->main_win, data->y, data->x + 1, "  ");
			wrefresh(data->main_win);
			data->x = data->x + 2;
		}
		if (!data->buffer[i] || len_hex(data->buffer[i]) == 1)
			print_zero(data);
		nprint_nb(data, 16, data->buffer[i], 97);
		mvwprintw(data->main_win, data->y, data->x + 1, " ");
		wrefresh(data->main_win);
		data->x = data->x + 1;
		i++;
		wait_or_enter(data, 10);
	}
	ft_bzero(data->buffer, 17);
}

int				fill_buff(t_data *data, unsigned char buff)
{
	if (data->i == 16)
	{
		data->i = 0;
		if (data->zero < 16)
		{
			data->zero = 0;
			print_buff(data);
			return (1);
		}
		if (data->check == 0)
		{
			data->x = 1;
			mvwprintw(data->main_win, data->y, data->x + 1, "*");
			wrefresh(data->main_win);
			data->y = data->y + 1;
			data->check = 1;
		}
		data->zero = 0;
		return (0);
	}
	return (0);
}
