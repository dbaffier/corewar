/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:23:33 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/21 20:02:09 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

void	op_aff(t_process *proc, t_op *op)
{
	// Affiche le char qui est donne en 1er param si il est nul carry = 1
	t_param		params[3];

	get_params_len(&params, 1, op->types, op->opcode);
	get_param_data(&params, 1, (char *)proc->file, (REG_SIZE)proc->pc);
	ft_printf("corewar : [%s] : \"%c\"\n", proc->name, params[0].param_data);
	proc->carry = params[0].param_data == 0 ? 1 : 0;
}
