/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:30:34 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/19 23:33:22 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		set_binary(t_data *data, int type)
{
	short bin;

	bin = data->t_bin;
	if (type == 1) ////////////// direct
	{
		bin = bin << 1;
		bin |= 1;
		bin <<= 1;
	}
	if (type == 2) /////////////// indirect
	{
		bin <<= 1;
		bin |= 1;
		bin <<= 1;
		bin |= 1;
	}
	if (type == 3) ////////////// registre
	{
		bin <<= 2;
		bin |= 1;
	}
	if (type == 0) ////////////// end or no arg
		bin <<= 2;
	data->t_bin = bin;
}

void		write_type(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		set_binary(data, data->type[i]);
		i++;
	}
	set_binary(data, 0);
	write(data->fd, &data->t_bin, 1);
}
