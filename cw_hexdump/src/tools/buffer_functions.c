/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 00:42:45 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 00:46:09 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			print_buff(t_data *data)
{
	int i;

	i = 0;
	while (data->buffer[i] || i < 16)
	{
		if (i % 8 == 0)
		{
			mvwprintw(data->main_win, data->y, data->x + 1, "  ");
			wrefresh(data->main_win);
			data->x = data->x + 2;
		}
		if (!data->buffer[i] || len_hex(data->buffer[i]) == 1)
		{
			mvwprintw(data->main_win, data->y, data->x + 1, "0");
			wrefresh(data->main_win);
			data->x = data->x + 1;
		}
		nprint_nb(data, 16, data->buffer[i], 97);
		mvwprintw(data->main_win, data->y, data->x + 1, " ");
		wrefresh(data->main_win);
		data->x = data->x + 1;
		i++;
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
