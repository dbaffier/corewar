/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 02:29:10 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 00:53:07 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		print_legend(t_data *data, int x, int y)
{
	mvwprintw(data->main_win, y - 1, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y, x, "%-4c%-15s%-27s%c", '|', "Magic number", "---", '|');
	wattron(data->main_win, COLOR_PAIR(1));
	mvwprintw(data->main_win, y, x + 25, "%s", "RED");
	reset_colors(data);
	mvwprintw(data->main_win, y + 1, x, "%-4c%-15s%-27s%c", '|', "Size", "---", '|');
	wattron(data->main_win, COLOR_PAIR(5));
	mvwprintw(data->main_win, y + 1, x + 25, "%s", "MAGENTA");
	reset_colors(data);
	mvwprintw(data->main_win, y + 2, x, "%-4c%-15s%-27s%c", '|', ".Name", "---", '|');
	wattron(data->main_win, COLOR_PAIR(2));
	mvwprintw(data->main_win, y + 2, x + 25, "%s", "GREEN");
	reset_colors(data);
	mvwprintw(data->main_win, y + 3, x, "%-4c%-15s%-27s%c", '|', ".Comment", "---", '|');
	wattron(data->main_win, COLOR_PAIR(3));
	mvwprintw(data->main_win, y + 3, x + 25, "%s", "YELLOW");
	reset_colors(data);
	mvwprintw(data->main_win, y + 4, x, "%-4c%-15s%-27s%c", '|', "Instructions", "---", '|');
	wattron(data->main_win, COLOR_PAIR(6));
	mvwprintw(data->main_win, y + 4, x + 25, "%s", "BLUE");
	reset_colors(data);
	mvwprintw(data->main_win, y + 5, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y + 6, x, "+---------------------------------------------+");

}

void		print_menu(t_data *data)
{
	int x;
	int y;

	x = 80;
	y = 3;
	mvwprintw(data->main_win, y, x, "+---------------------------------------------+");
	mvwprintw(data->main_win, y + 1, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y + 2, x, "%-4c%-15s%-6s%-21s%c", '|', "Pause", "---", "p", '|');
	mvwprintw(data->main_win, y + 3, x, "%-4c%-15s%-6s%-21s%c", '|', "Start", "---", "s", '|');
	mvwprintw(data->main_win, y + 4, x, "%-4c%-15s%-6s%-21s%c", '|', "Faster", "---", "enter", '|');
	mvwprintw(data->main_win, y + 5, x, "%-46c%c", '|', '|');
	mvwprintw(data->main_win, y + 6, x, "|=============================================|");
	print_legend(data, x, y + 8);
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
	mvwprintw(data->main_win, 1, 2, "Starting compiling into   >>");
	wrefresh(data->main_win);
	wattron(data->main_win, COLOR_PAIR(4) | A_BLINK);
	mvwprintw(data->main_win, 1, 35, "%s", data->file_name);
	wattroff(data->main_win, COLOR_PAIR(4) | A_BLINK);
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
