/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:42:45 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/21 18:50:28 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

// DIRECT_LOAD 0x02

void	op_ld(t_process *proc, t_op *op)
{
	// load le 1er parametre dans le registre passé en 2nd parametre
	// si le 1st param = 0 le carry passe a 1
	t_param		params[3];

	get_params_len(&params, 2, op->types, op->opcode);
	get_param_data(&params, 2, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[params[1].param_data] = (REG_SIZE)proc->pc +
		params[0].param_data % IDX_MOD;
	proc->carry = params[1].data == 0 ? 1 : 0;
}

// DIRECT STORE 0x03

void	op_st(t_process *proc, t_op *op)
{
	// inverse de load charge le registre passe en 1st param dans le 2nd param
	// meme fonctionnement pour le carry
	t_param		params[3];

	get_params_len(&params, 2, op->types, op->opcode);
	get_param_data(&params, 2, (char *)proc->file, (REG_SIZE)proc->pc);
	params[1].param_data = (REG_SIZE)proc->pc +
		reg[param[0].param_data] % IDX_MOD;
	proc->carry = params[1].data == 0 ? 1 : 0;
}

// ADD 0x04

void	op_add(t_process *proc, t_op *op)
{
	// ajoute le 1er param et le 2nd et stocke le resultat dans le 3eme
	// meme fonctionnement pour le carry
	t_param		params[3];

	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] = param[0].param_data + param[1].param_data;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}

// SUB 0x05

void	op_sub(t_process *proc, t_op *op)
{
	// soustraie le 1er param et le 2nd et stocke le resultat dans le 3eme
	// meme fonctionnement pour le carry
	t_param		params[3];

	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] = param[0].param_data - param[1].param_data;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}
