/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:59:16 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 23:17:56 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		write_param(t_data *data, t_token *tok, int *tab)
{
	int i;
	int len;

	i = 0;
	while (tok)
	{
		len = tab[i];
		while (len)
		{
			lseek(data->fd, data->pc + len, SEEK_SET);
			write(data->fd, &tok->val, 1);
			len--;
			data->pc = data->pc + 1;
		}
		/*write(data->fd, &tok->val, 1);//tab[i]);
		data->pc = data->pc + tab[i];*/
		tok = tok->next;
		i++;
	}
}
