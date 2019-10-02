/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 03:23:32 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/20 04:13:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		offset_calc(t_type *param, int nb)
{
	int		off;

	while (nb >= 0)
	{
		if (param[nb] & T_REG)
			off += 1;
		else if (param[nb] & T_DIR)
			off += 2;
		else if (param[nb] & T_IND)
			off += 4;
		else if (param[nb] & T_LAB)
			off += 8;
		 nb--;
	}
	return (off);
}	

int		get_param(void *data, int position, t_op *op, int pc)
{
	int		off;
	int		len;
	if (position == 1)
		off = 0;
	else if (position == 2)
	{
		off = offset_calc(op->reg_arg_type, 0);
		&& (op->reg_arg_type.one & T_REG))
	if (op->reg_arg_type.one & T_REG)
		;
}
