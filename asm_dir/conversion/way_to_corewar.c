/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_to_corewar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:36:59 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/21 21:48:14 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

int		way_to_corewar(t_data *data, t_aolist *ao)
{
	t_token *tok;

	while (ao && ao->tok == NULL)
		ao = ao->next;
	write_magic(data);
	if (!ft_strcmp(ao->tok->lab, NAME_CMD_STRING))
	{
		write_name(data, ao->tok->next->lab);
		ao = ao->next;
		write_comment(data, ao->tok->next->lab);
		ao = ao->next;
	}
	else
	{
		write_name(data, ao->next->tok->next->lab);
		write_comment(data, ao->tok->next->lab);
		ao = ao->next->next;
	}
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
