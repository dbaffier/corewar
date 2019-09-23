/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 02:29:10 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 03:26:26 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

int			wait_or_enter(t_data *data, int sleeping)
{
	char c;

	wtimeout(data->main_win, 0);
	while (sleeping-- > 0)
	{
		if ((c = wgetch(data->main_win)) == '\n')
			return (1);
		usleep(50000);
	}
	return (0);
}
