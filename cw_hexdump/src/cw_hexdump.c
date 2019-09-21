/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:03:52 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/21 03:15:02 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

int				cw_hexdump(t_data *data, char *file)
{
	int			fd;

	if ((fd = create_corfile(file)) < 0)
		return (ERR_OPEN);
	data->fd = fd;
	way_to_corewar(data);	
	return (0);
}

int				main(void)
{
	t_data	data;
	char	str[] = "test.s";

	ft_memset(&data, 0, sizeof(t_data));
	data.type[0] = DIRECT;
	data.type[1] = REGISTER;
	data.type[2] = 0;
	data.name = ft_strdup("HERE IS NAME BLLBLBLBL");
	data.comment = ft_strdup("COMMENT");
	data.size = 7;
	cw_hexdump(&data, str);
	return (0);
}
