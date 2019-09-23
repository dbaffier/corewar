/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 00:28:15 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 03:15:16 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		*thread_quit(void *thread)
{
	t_thread *arg;

	arg = thread;
	while (1)
	{
		char c = wgetch(arg->main_win);
		if (c == '\n')
		{
			arg->stop = 1;
			break;
		}
	}
	return(NULL);
}

int		print_first(t_data *data)
{
	WINDOW		*pad;
	pthread_t	thread;
	t_thread	arg;
	char		*msg;
	int			i;

	pad = newpad(1, 100);
	msg = ft_strdup("With this visu you will be able to see a bit more about how corewar works");
	ft_memset(&arg, 0, sizeof(t_thread));
	arg.main_win = data->main_win;
	pthread_create(&thread, NULL, thread_quit, &arg);
	while (!arg.stop)
	{
		if (msg && msg[i])
		{
			waddch(pad, msg[i]);
			copywin(pad, data->main_win, 0, 0, 10, 5, 10, 5 + 100, 0);
			wrefresh(data->main_win);
			wait_or_enter(data, 1);
			i++;
		}
		else
		{
			wattron(data->main_win, A_BLINK);
			mvwprintw(data->main_win, 12, 55, "Press enter to continue...", 123);
			wattroff(data->main_win, A_BLINK);
			wrefresh(data->main_win);
		}
	}
	wclear(data->main_win);
	wrefresh(data->main_win);
	return (0);
}

int		init_screen(t_data *data)
{
	initscr();
	clear();
	refresh();
	cbreak();
	noecho();
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	data->main_win = newwin(0, 0, 0, 0);
	wattron(data->main_win, COLOR_PAIR(0));
	wrefresh(data->main_win);
	print_first(data);
	return (0);
}
