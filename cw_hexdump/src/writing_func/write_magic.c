/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:29:53 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/20 22:55:13 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		write_magic(t_data *data)
{
	int		zero;
	int		magic;

	zero = 0x0;
	magic = 0xf383ea;
	write(data->fd, &zero, 1);
	write(data->fd, &magic, 3);
}
