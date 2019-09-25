/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 02:29:10 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/25 19:12:17 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		print_menu(t_data *data)
{
	int x;
	int y;

	x = 100;
	y = 5;
	mvwprintw(data->main_win, y, x + 1, "---------------------------------------------");
	wrefresh(data->main_win);
	mvwprintw(data->main_win, y + 1, x, "|   Pause   ---\t\t[p]\t\t  |");
	wrefresh(data->main_win);
	mvwprintw(data->main_win, y + 2, x, "|   Start   ---\t\t[s]\t\t  |");
	wrefresh(data->main_win);
	mvwprintw(data->main_win, y + 3, x, "|   Faster  ---\t\t[enter]\t\t  |");
	wrefresh(data->main_win);
	mvwprintw(data->main_win, y + 4, x + 1, "---------------------------------------------");
	wrefresh(data->main_win);
}

int			wait_or_enter(t_data *data, int sleeping)
{
	char c;
	int pause;

	wtimeout(data->main_win, 0);
	pause = 100;
	while (sleeping-- > 0)
	{
		if ((c = wgetch(data->main_win)) == '\n')
			return (1);
		if (c == 'p')
		{	
			while (pause--)
			{
				if ((c = wgetch(data->main_win)) == 's')
					break ;
				usleep(50000);
			}
		}
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
