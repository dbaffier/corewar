/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:12:05 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/23 02:23:37 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

/*
** STI 0x0B
** additione les deux derniers param et va changer la valeur a l'adresse de
** l'addition avec la valeur dans le registre passé en 1eme parametre
** si l'addition = 0 le carry passe a 1
*/

void	op_sti(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	char		addr;
	t_process	*proc;

	proc = e->proc[i];
	get_params_len(&params, 3, op->types, op->opcode);
	get_param_data(&params, 3, (char *)proc->file, (REG_SIZE)proc->pc);
	addr = (params[1].param_data + params[2].param_data) % IDX_MOD;
	(char *)proc->file[addr] = proc->reg[params[0].param_data];
	proc->carry = addr == 0 ? 1 : 0;
}


/*
**FORK 0x0C
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah jsp
*/

void	op_fork(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = &e->proc[i];
	get_params_len(&params, 1, op->types, op->opcode);
	get_param_data(&params, 1, (char *)proc->file, (REG_SIZE)proc->pc);
	if (params[0].param_data != 0)
	{
		ft_memcpy(proc->next_proc, proc, sizeof(t_process));
		proc->next->proc->pc = (proc->pc + params[0].param_data) % IDX_MOD;
	}                     
}

/*
** LLD 0x0D
** direct load sans le %IDX_MOD
** si le 1st param = 0 le carry passe a 1
*/

void	op_lld(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = e->proc[i];
	get_params_len(&params, 2, op->types, op->opcode);
	get_param_data(&params, 2, (char *)proc->file, (REG_SIZE)proc->pc);
	proc->reg[params[1].param_data] = (REG_SIZE)proc->pc + params[0].param_data;
	proc->carry = params[1].data == 0 ? 1 : 0;
}

/*
**LLDI 0x0E
** ldi sans restriction d'adressage
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
	addr = (params[0].param_data + params[1].param_data);
	proc->reg[params[2].param_data] = (char *)proc->file[addr];
	proc->carry = addr == 0 ? 1 : 0;
}

/*
** LFORK 0x0F
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah jsp
*/

void	op_lfork(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = e->proc[i];
	get_params_len(&params, 1, op->types, op->opcode);
	get_param_data(&params, 1, (char *)proc->file, (REG_SIZE)proc->pc);
	ft_memcpy(proc->next_proc, proc, sizeof(t_process));
	proc->next->proc->pc = proc->pc + params[0].param_data;
}
