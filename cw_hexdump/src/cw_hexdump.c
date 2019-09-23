/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:03:52 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 03:28:51 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			print_head(t_data *data)
{
	char c;
	int i;
	int pause;

	i = 0;
	pause = 0;
	while (1)
	{
		if (pause == 0)
		{
			wattron(data->main_win, COLOR_PAIR(2));
			mvwprintw(data->main_win, 1, 2, "%s", data->file_name);
			wattroff(data->main_win, COLOR_PAIR(2));
			wrefresh(data->main_win);	
			mvwprintw(data->main_win, 1, ft_strlen(data->file_name) + 3, "created");
			wrefresh(data->main_win);	
			while (i++ < 3)
			{
				mvwprintw(data->main_win, 1, ft_strlen(data->file_name) + 10 + i, ".\t");
				wrefresh(data->main_win);
				if (wait_or_enter(data, 10))
					break ;
			}
			wclear(data->main_win);
			wrefresh(data->main_win);
			mvwprintw(data->main_win, 1, 2, "Starting compiling into :");
			wrefresh(data->main_win);	
			wattron(data->main_win, COLOR_PAIR(2)|A_BLINK);
			mvwprintw(data->main_win, 1, 30, "%s", data->file_name);
			wattroff(data->main_win, COLOR_PAIR(2)|A_BLINK);
			wrefresh(data->main_win);	
			pause = 1;
		}
		if ((c = wgetch(data->main_win)) == '\n')
			break;
	}
}

int				cw_hexdump(t_data *data, char *file)
{
	if ((data->fd = create_corfile(file)) < 0)
		return (ERR_OPEN);
	if (data->flag & FLAG_N)
		print_head(data);
	way_to_corewar(data);	
	return (0);
}

int				main(int ac, char **av)
{
	t_data	data;
	char	str[] = "test.s";

	ft_memset(&data, 0, sizeof(t_data));
	if (av[1] && ft_strcmp(av[1], "-n") == 0)
	{
		data.flag |= FLAG_N;
		init_screen(&data);
	}
	data.type[0] = DIRECT;
	data.type[1] = REGISTER;
	data.type[2] = 0;
	data.name = ft_strdup("HERE IS MY NAME BLUBLUBLU");
	data.comment = ft_strdup("COMMENT");
	data.size = 21;
	data.file_name = ft_strdup("test.cor");
	cw_hexdump(&data, str);
	endwin();
	close(data.fd);
	return (0);
}
