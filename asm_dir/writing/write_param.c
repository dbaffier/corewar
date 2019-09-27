/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:59:16 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 00:24:59 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		write_param(t_data *data, t_token *tok, int *tab)
{
	int i;

	i = 0;
	while (tok)
	{
		write(data->fd, &tok->val, tab[i]);
		data->pc = data->pc + tab[i];
		tok = tok->next;
		i++;
	}
}
