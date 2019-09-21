/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations6_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:51:30 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/21 20:02:08 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

// AND 0x06

void	op_and(t_process *proc, t_op *op)
{
	// AND avec le 1er param et le 2nd et stock le resultat dans le 3eme
	// meme fonctionnement pour le carry
	t_param		params[3];

	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] =
		(param[0].param_data & param[1].param_data) % IDX_MOD;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}

// OR 0x07

void	op_or(t_process *proc, t_op *op)
{
	// OR avec le 1er param et le 2nd et stock le resultat dans le 3eme
	// meme fonctionnement pour le carry
	t_param		params[3];

	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] =
	(param[0].param_data | param[1].param_data) % IDX_MOD;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}

// XOR 0x08

void	op_xor(t_process *proc, t_op *op)
{
	// XOR avec le 1er param et le 2nd et stock le resultat dans le 3eme
	// meme fonctionnement pour le carry
	t_param		params[3];

	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] =
		(param[0].param_data ^ param[1].param_data) % IDX_MOD;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}

// ZJMP 0x09

void	op_zjmp(t_process *proc, t_op *op)
{
	// jump a l'adresse donnee en parametre si le carry est a un, sinon fail
	t_param		params[3];

	if (proc->carry == 1)
	{
		get_params_len(&params, 1, op->types, op->opcode);
		get_param_data(&params, 1, (char *)proc->file, (REG_SIZE)proc->pc);
		op->direct_size += param[0].param_data;
	}
}

// LDI 0x0A

void	op_ldi(t_process *proc, t_op *op)
{
	// additione les deux premiers param et va chercher a l'adresse de
	// l'addition la valeur a ajouter dans le registre passé en 3eme parametre
	// si l'addition = 0 le carry passe a 1
	t_param		params[3];
	char		addr;

	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	addr = (params[0].param_data + params[1].param_data) % IDX_MOD;
	proc->reg[params[2].param_data] = (char *)proc->file[addr];
	proc->carry = addr == 0 ? 1 : 0;
}

