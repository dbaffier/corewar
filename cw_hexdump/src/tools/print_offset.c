#include "cw_hexdump.h"

void	print_offset(t_data *data)
{
	int offset;
	int loop;
	int x;
	int mod;

	offset = data->pos;
	loop = 7;
	x = 7;
	while (loop--)
	{
		mod = offset % 16;
		if (offset == 0)
			mvwprintw(data->main_win, data->y, x, "0");
		else
		{
			if (mod > 9)
				mvwprintw(data->main_win, data->y, x, "%c", (mod - 10) + 97);
			if (mod <= 9)
				mvwprintw(data->main_win, data->y, x, "%c", mod + 48);
		}
		wrefresh(data->main_win);
		x--;
		offset /= 16;
	}
	data->x = data->x + 8;
}
