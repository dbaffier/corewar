/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:42:45 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/23 03:20:26 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

/*
** LIVE 0x01
** renvoie un live pour le processus qui l'appelle
** si le 1st param = 0 le carry passe a 1
*/

void	op_live(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = &e->proc[i];
	get_params_len(params, 1, op->types, op->opcode);
	get_param_data(params, 1, (char *)proc->file, (int)proc->pc);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if ((int)params[0].param_data == e->proc[i].id)
		{
			e->proc[i].cycle_left = CYCLE_TO_DIE;
			ft_printf("corewar : Player [%d] is alive. Keep fighting.\n",
					e->proc[i].id);
			return ;
		}
		i++;
	}
	ft_printf("corewar : Wrong parameter [%d] player id does not exist . No one to keep alive.\n", params[0].param_data);
}

/*
** DIRECT_LOAD 0x02
** load le 1er parametre dans le registre passé en 2nd parametre
** si le 1st param = 0 le carry passe a 1
*/

void	op_ld(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;
	int			reg;
	int			parameter;

	proc = &e->proc[i];
	get_params_len(params, 2, op->types, op->opcode);
	get_param_data(params, 2, (char *)proc->file, (int)proc->pc);
	reg = ft_atoi_base(params[1].param_data, "0123456789");
	parameter = ft_atoi_base(params[0].param_data, "01234556789");
	*(REG_CAST *)proc->reg[reg] = (REG_CAST)proc->pc + parameter % IDX_MOD;
	proc->carry = (reg == 0) ? 1 : 0;
}

/*
** DIRECT STORE 0x03
** inverse de load charge le registre passe en 1st param dans le 2nd param
** meme fonctionnement pour le carry
*/

void	op_st(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = &e->proc[i];
	get_params_len(params, 2, op->types, op->opcode);
	get_param_data(params, 2, (char *)proc->file, (REG_CAST)proc->pc);
	*(REG_CAST *)params[1].param_data = (REG_CAST)proc->pc +
		(REG_CAST)proc->reg[(REG_CAST)params[0].param_data] % IDX_MOD;
	proc->carry = ((REG_CAST)params[1].param_data == 0) ? 1 : 0;
}

/*
** ADD 0x04
** ajoute le 1er param et le 2nd et stocke le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_add(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = &e->proc[i];
	get_params_len(params, 3, op->types, op->opcode);
	get_param_data(params, 3, (char *)proc->file, (REG_CAST)proc->pc);
	*(REG_CAST *)proc->reg[(REG_CAST)params[2].param_data] =
		(REG_CAST)params[0].param_data + (REG_CAST)params[1].param_data;
	proc->carry = ((REG_CAST)proc->reg[(REG_CAST)params[2].param_data] == 0) ?
		1 : 0;
}

/*
** SUB 0x05
** soustraie le 1er param et le 2nd et stocke le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_sub(t_op *op, t_env *e, int i)
{
	t_param		params[3];
	t_process	*proc;

	proc = &e->proc[i];
	get_params_len(params, 3, op->types, op->opcode);
	get_param_data(params, 3, (char *)proc->file, (REG_CAST)proc->pc);
	*(REG_CAST *)proc->reg[(REG_CAST)params[2].param_data] =
		(REG_CAST)params[0].param_data - (REG_CAST)params[1].param_data;
	proc->carry = ((REG_CAST)proc->reg[(REG_CAST)params[2].param_data] == 0) ?
		1 : 0;
}
