/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations6_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:51:30 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/01 20:00:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

extern struct s_op	op_tab[17];

/*
** AND 0x06
** AND avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_and(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;

	get_params_len(params, 3,
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 6);
	get_params_data(params, 3,
			((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	*(REG_CAST *)proc->reg[params[2].value] =
		(params[0].value & params[1].value) % IDX_MOD;
	proc->carry = (params[0].value & params[1].value) == 0 ? 1 : 0;
	len = full_len_size(op_tab[5].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** OR 0x07
** OR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_or(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;

	get_params_len(params, 3,
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 7);
	get_params_data(params, 3,
			((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	*(REG_CAST *)proc->reg[params[2].value] =
		(params[0].value | params[1].value) % IDX_MOD;
	proc->carry = (params[0].value | params[1].value) == 0 ? 1 : 0;
	len = full_len_size(op_tab[6].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** XOR 0x08
** XOR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_xor(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;

	get_params_len(params, 3,
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 8);
	get_params_data(params, 3,
			((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	*(REG_CAST *)proc->reg[params[2].value] =
		(params[0].value ^ params[1].value) % IDX_MOD;
	proc->carry = (params[0].value ^ params[1].value) == 0 ? 1 : 0;
	len = full_len_size(op_tab[7].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** ZJMP 0x09
** jump a l'adresse donnee en parametre si le carry est a un, sinon fail
*/

void	op_zjmp(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;

	ft_bzero(params, sizeof(params));
	if (proc->carry == 1)
	{
		get_params_len(params, 1,
				*((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 9);
		get_params_data(params, 1,
				((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
		if (e->ncu.info_win)
			wprintw(e->ncu.info_win, "jump to :[%hd]\n", params[0].value);
		move_process_pc(proc, params[0].value, e);
		return ;
	}
	len = full_len_size(op_tab[8].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** LDI 0x0A
** additione les deux premiers param et va chercher a l'adresse de
** l'addition la valeur a ajouter dans le registre passé en 3eme parametre
** si l'addition = 0 le carry passe a 1
*/

void	op_ldi(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			addr;
	int			len;

	get_params_len(params, 3,
			*((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 10);
	get_params_data(params, 3,
			((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	addr = (params[0].value + params[1].value) % IDX_MOD;
	*(REG_CAST *)proc->reg[params[2].value] =
		((unsigned char *)e->arena)[*(REG_CAST *)proc->pc + addr];
	proc->carry = addr == 0 ? 1 : 0;
	len = full_len_size(op_tab[9].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}
