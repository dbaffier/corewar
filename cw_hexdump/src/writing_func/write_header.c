/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:35:20 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/21 03:22:44 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		write_name(t_data *data)
{
	int		i;
	int		zero;
	short	bin;

	i = 0;
	zero = 0x0;
	while (data->name && data->name[i])
	{
		bin = binary(data->name[i]);
		write(data->fd, &bin, 1);
		i++;
	}
	while (i++ < 128 + 7)
		write(data->fd, &zero, 1);
	write(data->fd, &data->size, 1);
}

static void		write_comment(t_data *data)
{
	int		i;
	int		zero;
	short	bin;

	i = 0;
	zero = 0x0;
	while (data->comment && data->comment[i])
	{
		bin = binary(data->comment[i]);
		write(data->fd, &bin, 1);
		i++;
	}
	while (i++ < 2048 - (128 + 8 + 4))
		write(data->fd, &zero, 1);
}

void			write_header(t_data *data, int type)
{
	if (type == NAME)
		write_name(data);
	if (type == COMMENT)
		write_comment(data);
}
