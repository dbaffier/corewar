/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_to_corewar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:36:59 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 00:16:42 by mmonier          ###   ########.fr       */
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
		if (tok->type == LABEL)
			tok = tok->next;
		write_opc(data, tok->val);
		write_type(data, ao->arg);
		write_param(data, tok->next, ao->arg_size);
	}
	return (0);
}
