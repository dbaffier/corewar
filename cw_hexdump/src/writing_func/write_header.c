/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:35:20 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 02:38:13 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		write_name(t_data *data)
{
	int	i;

	i = 0;
	while (data->name && data->name[i])
		write(data->fd, &data->name[i++], 1);
	lseek(data->fd, 135 + PADDING, SEEK_SET);
	write(data->fd, &data->size, 1);
}

static void		write_comment(t_data *data)
{
	int		i;

	i = 0;
	while (data->comment && data->comment[i])
		write(data->fd, &data->comment[i++], 1);
	lseek(data->fd, 2192, SEEK_SET);
	data->pc = 2191;
}

void			write_header(t_data *data, int type)
{
	if (type == NAME)
		write_name(data);
	if (type == COMMENT)
		write_comment(data);
}
