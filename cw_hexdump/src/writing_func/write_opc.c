/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_opc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:35:31 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/21 02:52:30 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void	write_opc(t_data *data, char *opc)
{
	static t_opc	tab[17] = {LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMP,
							LDI, STI, FORK, LLD, LLDI, LFORK, AFF};
	int				i;

	i = 0;
	while (ft_strcmp(opc, tab[i].opcode) != 0)
		i++;
	write(data->fd, &tab[i].code, 1);
}
