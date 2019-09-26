/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:59:16 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 23:54:51 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		write_param(t_data *data, char *param, int size)
{
	short	dec;
	short	bin;

	dec = ft_atoi(param);
	bin = binary(dec);
	lseek(data->fd, data->pc + size, SEEK_SET);
	write(data->fd, &bin, 1);
	data->pc = data->pc + size;
}
