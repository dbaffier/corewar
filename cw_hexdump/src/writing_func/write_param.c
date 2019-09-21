/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:59:16 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/21 19:19:31 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		write_param(t_data *data, char *param, int size)
{
	short	dec;
	short	bin;
	short	zero;

	dec = ft_atoi(param);
	bin = binary(dec);
	zero = 0x0;
	while (size--)
		write(data->fd, &zero, 1);
	write(data->fd, &bin, 1);
}
