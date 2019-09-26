/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:30:34 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 01:12:45 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		set_binary(t_data *data, int type)
{
	short bin;

	bin = data->t_bin;
	if (type == DIRECT)
	{
		bin = bin << 1;
		bin |= 1;
		bin <<= 1;
	}
	if (type == INDIRECT)
	{
		bin <<= 1;
		bin |= 1;
		bin <<= 1;
		bin |= 1;
	}
	if (type == REGISTER)
	{
		bin <<= 2;
		bin |= 1;
	}
	if (type == 0)
		bin <<= 2;
	data->t_bin = bin;
}

void			write_type(t_data *data)
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
	data->pc = data->pc + 1;
}
