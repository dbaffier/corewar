/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_to_corewar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:36:59 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/19 00:52:18 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdup.h"

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

void	write_type(t_data *data, int type)
{
	if (type & DIRECT)
	{
	}
	if (type & UNDIRECT)
	{
	}
	if (type & REGISTRE)
	{
	}
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
