/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendersyntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:26:08 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/04 23:46:58 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	rendersyntax(t_print *print, t_val *val, unsigned char buff)
{
	val->size = 1;
	if (val->type == E_OPCODE || print->ninstruc == 0)
	{
		if (buff == 1 || buff == 9 || buff == 12 || buff == 15)
		{
			val->type = E_INSTRUC;
			val->ebyte = 0;
		}
		else
			val->type = E_EBYTE;
	}
	else if (val->type == E_EBYTE)
		decode(print, buff);
	else if (val->type == E_INSTRUC)
	{
		if (val->ebyte == 1)
		{
			if (print->param[print->idx] == E_REG)
				val->size = 1;
			else if (print->param[print->idx] == E_DIR)
				val->size = 4;
			else if (print->param[print->idx] == E_IND)
				val->size = 2;
		}
		else
			val->size = 4;
		print->ninstruc -= 1;
		print->idx += 1;
	}
}
