/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:17:43 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 00:58:15 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void	print_end(t_data *data)
{
	char c;
	char *str;

	data->y = data->y + 2;
	data->x = 4;
	if (!(str = (char *)malloc(sizeof(char) * 6)))
		return ;
	mvwprintw(data->main_win, data->y, data->x, "-- Press [esc] to quit");
	mvwprintw(data->main_win, data->y + 1, data->x, "-- Press [ r ] to reprint");
	while (1)
	{
		c = wgetch(data->main_win);
		if (c == 27)
			break ;
		if (c == 114)
		{
			wclear(data->main_win);
			print_compilation(data);
			print_menu(data);
			print_hex(data);
			print_end(data);
		}
	}
}
