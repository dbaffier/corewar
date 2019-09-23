/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 22:23:29 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 00:47:18 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

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
		mvwprintw(arg->main_win, 0, 0, "Press enter to skip", 123);
	}
	return(NULL);
}

int			print_first(t_info *info)
{
	WINDOW	*pad;
	pthread_t thread;
	t_thread arg;
	char	*msg;
	int		i = 0;
	int		x = 5;
	int		y = 10;

	pad = newpad(1, 100);
	msg = ft_strdup("With this visu you will be able to see a bit much about how corewar works");
	ft_memset(&arg, 0, sizeof(t_thread));
	arg.main_win = info->main_win;
	pthread_create(&thread, NULL, thread_quit, &arg);
	while (!arg.stop)
	{
		if (msg && msg[i])
		{
			waddch(pad, msg[i]);
			copywin(pad, info->main_win, 0, 0, 10, 5, 10, 5 + 100, 0);
			wrefresh(info->main_win);
			usleep(50000);
			i++;
		}
	}
	return (0);
}

int			init_screen(t_info *info)
{
	WINDOW	*win;

	initscr();
	refresh();
	cbreak();
	noecho();
	//start_color();
	info->main_win = newwin(0, 0, 0, 0);
	return (0);
}

int			print_file(t_info *info)
{
	WINDOW *pad;
	int ret;
	char buff[2];

	pad = newpad(1, 100);
	while ((ret = read(info->fd, &buff, 1)) > 0)
	{
		waddch(pad, buff[0]);
		copywin(pad, info->main_win, 0, 0, 10, 5, 10, 5 + 100, 0);
		wrefresh(info->main_win);
		usleep(50000);
		buff[ret] = '\0';

	}
	return (0);
}

int			main(int ac, char **av)
{
	t_info info;

	ft_memset(&info, 0, sizeof(t_info));
	info.fd = open(av[1], O_RDONLY);
	init_screen(&info);
	print_first(&info);
	print_file(&info);
	endwin();
	close(info.fd);
	return (0);
}
