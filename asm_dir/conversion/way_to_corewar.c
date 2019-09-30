/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_to_corewar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:36:59 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/30 23:43:21 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

int		way_to_corewar(t_data *data, t_aolist *ao)
{
	t_token *tok;

	write_magic(data);
	write_name(data, ao->tok->next->lab);
	ao = ao->next;
	write_comment(data, ao->tok->next->lab);
	ao = ao->next;
	while (ao)
	{
		tok = ao->tok;
		if (tok && tok->type & LABEL)
			tok = tok->next;
		if (tok)
		{
			write_opc(data, tok->val);
			if (data->encoding_byte)
				write_type(data, ao->arg);
			write_param(data, tok->next, ao->arg_size);
		}
		ao = ao->next;
	}
	return (0);
}