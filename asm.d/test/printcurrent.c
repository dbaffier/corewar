/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcurrent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:10:13 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/05 00:27:07 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static char		*readtype(int idx, int *param)
{
	if (param[idx] == E_REG)
		return ("REGISTER");
	if (param[idx] == E_DIR)
		return ("DIRECT");
	return ("INDIRECT");
}
static void		printtype(t_print *print, t_val *val)
{
	if (print->pos == 1)
		return ;
	if (val->type == E_MAGIC)
		ft_printf("This is the magic number ");
	else if (val->type == E_NAME)
		ft_printf("Writting name ");
	else if (val->type == E_PAD)
		ft_printf("Writting padding ");
	else if (val->type == E_SIZE)
		ft_printf("writting size ");
	else if (val->type == E_COMMENT)
		ft_printf("Writting comment ");
	else if (val->type == E_OPCODE)
		ft_printf("Writting opcode ");
	else if (val->type == E_EBYTE && val->ebyte == 1)
		ft_printf("Writting encoding byte ");
	else if (val->type == E_INSTRUC && val->ebyte == 1) 
		ft_printf("Writting %d instruction type %s ", 
				print->idx, readtype(print->idx, print->param));
	else if (val->type == E_INSTRUC && val->ebyte == 0) 
		ft_printf("Writting instructiom type DIRECT ");
}

void			printcurrent(t_print *print, unsigned char buff)
{
	ft_printf("0%x ", buff);
	printtype(print, print->val);
}
