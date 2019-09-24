/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 02:29:10 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 01:50:17 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

int			wait_or_enter(t_data *data, int sleeping)
{
	char c;

	wtimeout(data->main_win, 0);
	while (sleeping-- > 0)
	{
		if ((c = wgetch(data->main_win)) == '\n')
			return (1);
		usleep(50000);
	}
	return (0);
}

void		print_file_name(t_data *data)
{
	wattron(data->main_win, COLOR_PAIR(2));
	mvwprintw(data->main_win, 1, 2, "%s", data->file_name);
	wattroff(data->main_win, COLOR_PAIR(2));
	wrefresh(data->main_win);
	mvwprintw(data->main_win, 1, ft_strlen(data->file_name) + 3, "created");
	wrefresh(data->main_win);
}

void		print_compilation(t_data *data)
{
	wclear(data->main_win);
	wrefresh(data->main_win);
	mvwprintw(data->main_win, 1, 2, "Starting compiling into :");
	wrefresh(data->main_win);
	wattron(data->main_win, COLOR_PAIR(2) | A_BLINK);
	mvwprintw(data->main_win, 1, 30, "%s", data->file_name);
	wattroff(data->main_win, COLOR_PAIR(2) | A_BLINK);
	wrefresh(data->main_win);
}

void		print_dot(t_data *data)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(data->file_name);
	while (i++ < 3)
	{
		mvwprintw(data->main_win, 1, len + 10 + i, ".\t");
		wrefresh(data->main_win);
		if (wait_or_enter(data, 10))
			break ;
	}
}
