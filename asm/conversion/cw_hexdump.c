/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:03:52 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 00:18:09 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		print_head(t_data *data)
{
	char		c;
	int			pause;

	pause = 0;
	while (1)
	{
		if (pause == 0)
		{
			print_file_name(data);
			print_dot(data);
			print_compilation(data);
			pause = 1;
		}
		if ((c = wgetch(data->main_win)) == '\n')
			break ;
	}
}

static int				cw_hexdump(t_data *data, char *file)
{
	if ((data->fd = create_corfile(file)) < 0)
		return (ERR_OPEN);
	if (data->flag & FLAG_N)
		print_head(data);
	way_to_corewar(data);
	return (0);
}

static void		init_data(t_data *data, t_env *e)
{
	data->e = e;
	data->ao = e->aolist;
}

int				dump_to_file(t_env *e, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (parse_flag(&data, av) == ERR_FLAG)
		print_usage(ERR_FLAG);
	if (data.flag & FLAG_N)
		init_screen(&data);
	cw_hexdump(&data, str);
	if (data.flag & FLAG_N)
	{
		print_menu(&data);
		print_hex(&data);
		print_end(&data);
		endwin();
	}
	if ((data.flag & FLAG_O) && !(data.flag & FLAG_N))
		print_fsize(&data);
	if ((data.flag & FLAG_P) || (data.flag & FLAG_GP))
		print_path(&data);
	close(data.fd);
	return (0);
}
