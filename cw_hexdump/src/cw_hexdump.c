/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:03:52 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 00:56:39 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			print_head(t_data *data)
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
	print_hex(&data);
	endwin();
	close(data.fd);
	return (0);
}
