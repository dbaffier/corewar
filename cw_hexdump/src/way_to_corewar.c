/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_to_corewar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:36:59 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/19 23:23:04 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdup.h"

void	set_binary(t_data *d, int type)
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

void	write_type(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		set_binary(data, data->tab[i]);
		i++;
	}
	set_binary(data, 0);
	bin_to_hex(data);
}

void	write_opc(t_data *data, char *opc)
{
	static t_opc	tab[17] = {LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMP,
							LDI, STI, FORK, LLD, LLDI, LFORK, AFF};
	int				i;

	i = 0;
	while (ft_strcmp(opc, tab[i].opcode) != 0)
		i++;
	write(data->fd, &tab[i].code, 2);
	data->cursor = data->cursor + 2;
}

int		way_to_corewar(t_data *data)
{
	while ()
	{
		if ()
			write_opc(data, opc);
		if ()
			write_type(data, type);
		if ()
			write_arg(data, arg);

	}
	return (0);
}

direct --> %
indirect --> pas %
registre --> peut y avoir un %

10 10 01 00
