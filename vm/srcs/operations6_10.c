/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations6_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:51:30 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/23 03:20:20 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

/*
** AND 0x06
** AND avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_and(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = e->proc[i];
	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] =
		(param[0].param_data & param[1].param_data) % IDX_MOD;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}

/*
** OR 0x07
** OR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_or(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = e->proc[i];
	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] =
	(param[0].param_data | param[1].param_data) % IDX_MOD;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}

/*
** XOR 0x08
** XOR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_xor(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = e->proc[i];
	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[param[2].param_data] =
		(param[0].param_data ^ param[1].param_data) % IDX_MOD;
	proc->carry = proc->reg[params[2].data] == 0 ? 1 : 0;
}

/*
** ZJMP 0x09
** jump a l'adresse donnee en parametre si le carry est a un, sinon fail
*/

void	op_zjmp(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = e->proc[i];
	if (proc->carry == 1)
	{
		get_params_len(&params, 1, op->types, op->opcode);
		get_param_data(&params, 1, (char *)proc->file, (REG_SIZE)proc->pc);
		op->direct_size += param[0].param_data;
	}
}

/*
** LDI 0x0A
** additione les deux premiers param et va chercher a l'adresse de
** l'addition la valeur a ajouter dans le registre passé en 3eme parametre
** si l'addition = 0 le carry passe a 1
*/

void	op_ldi(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	char		addr;
	t_process	*proc;

	proc = e->proc[i];
	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	addr = (params[0].param_data + params[1].param_data) % IDX_MOD;
	proc->reg[params[2].param_data] = (char *)proc->file[addr];
	proc->carry = addr == 0 ? 1 : 0;
}
