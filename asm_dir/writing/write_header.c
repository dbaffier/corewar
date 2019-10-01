/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:35:20 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/01 01:08:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void			write_name(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		write(data->fd, &str[i++], 1);
	lseek(data->fd, 135 + 4, SEEK_SET);
	write(data->fd, &data->e->size, 4);
}

void			write_comment(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
		write(data->fd, &str[i++], 1);
	lseek(data->fd, 2192, SEEK_SET);
	data->pc = 2191;
}
