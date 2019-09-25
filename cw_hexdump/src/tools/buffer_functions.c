/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 00:42:45 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/25 23:56:42 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			reset_colors(t_data *data)
{
	wattroff(data->main_win, COLOR_PAIR(0));
	wattroff(data->main_win, COLOR_PAIR(1));
	wattroff(data->main_win, COLOR_PAIR(2));
	wattroff(data->main_win, COLOR_PAIR(3));
	wattroff(data->main_win, COLOR_PAIR(4));
	wrefresh(data->main_win);
}

void			starting_color(t_data *data)
{
	reset_colors(data);
	if (data->pos >= 0 && data->pos <= 4)
		wattron(data->main_win, COLOR_PAIR(1));
	else if (data->pos > 4 && data->pos <= 132)						///name
		wattron(data->main_win, COLOR_PAIR(2));
	else if (data->pos > 132 && data->pos <= 136)						///padding
		wattron(data->main_win, COLOR_PAIR(0));
	else if (data->pos > 136 && data->pos <= 140)						///size
		wattron(data->main_win, COLOR_PAIR(5));
	else if (data->pos > 140 && data->pos < 2188)						///comment
		wattron(data->main_win, COLOR_PAIR(3));
	else if (data->pos >= 2188 && data->pos < 2192)						///comment
		wattron(data->main_win, COLOR_PAIR(0));
	else if (data->pos >= 2192)										///instructions
		wattron(data->main_win, COLOR_PAIR(6));
	else
		wattron(data->main_win, COLOR_PAIR(0));
}

void			print_zero(t_data *data)
{
	mvwprintw(data->main_win, data->y, data->x + 1, "0");
	wrefresh(data->main_win);
	data->x = data->x + 1;
}

void			print_zero_line(t_data *data)
{
	int i;

	i = 0;
	data->x = 3;
	while (ZERO_LINE[i])
	{
		if (ZERO_LINE[i] == ' ')
			data->pos = data->pos + 1;
		mvwprintw(data->main_win, data->y, data->x + 1, "%c", ZERO_LINE[i++]); 
		wrefresh(data->main_win);
		data->x = data->x + 1;
		wait_or_enter(data, 3);
	}
	data->x = 1;
	data->y = data->y + 1;
	mvwprintw(data->main_win, data->y, data->x + 2, "*");
	wrefresh(data->main_win);
	data->check = 1;
	data->y = data->y + 1;
}

void			print_buff(t_data *data)
{
	int i;

	i = 0;
	while (data->buffer[i] || i < 16)
	{
		starting_color(data);
		data->pos = data->pos + 1;
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
			print_zero_line(data);
		else
			data->pos = data->pos + 16;
		data->zero = 0;
		return (0);
	}
	return (0);
}
