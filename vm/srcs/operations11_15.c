/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:12:05 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/25 13:24:21 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

extern t_op op_tab[17];

/*
** STI 0x0B
** additione les deux derniers param et va changer la valeur a l'adresse de
** l'addition avec la valeur dans le registre passé en 1eme parametre
** si l'addition = 0 le carry passe a 1
*/

void	op_sti(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			addr;
	int			len;
	int			i;

	i = 0;
	get_params_len(params, 3, *((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 11);
	get_params_data(params, 3, ((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	addr = (params[1].value + params[2].value) % IDX_MOD;
	((unsigned char *)e->arena)[*(REG_CAST *)proc->pc + addr] = *(REG_CAST *)proc->reg[params[0].value];
	proc->carry = addr == 0 ? 1 : 0;
	len = full_len_size(op_tab[10].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
**FORK 0x0C
** Cree un nouveau processus
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle du coup
*/

void	op_fork(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;
	int			i;

	i = 0;
	get_params_len(params, 1, *((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 12);
	get_params_data(params, 1, ((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	if (params[0].value != 0)
		proc->next = new_proc(proc, params[0].value, 0);
	len = full_len_size(op_tab[11].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** LLD 0x0D
** direct load sans le %IDX_MOD
** si le 1st param = 0 le carry passe a 1
*/

void	op_lld(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;
	int			i;

	i = 0;
	get_params_len(params, 2, *((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 13);
	get_params_data(params, 2, ((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	*(REG_CAST *)proc->reg[params[1].value] = *(REG_CAST *)proc->pc + params[0].value;
	proc->carry = params[1].value == 0 ? 1 : 0;
	len = full_len_size(op_tab[12].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** LLDI 0x0E
** ldi sans restriction d'adressage
** si l'addition = 0 le carry passe a 1
*/

void	op_lldi(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			addr;
	int			len;
	int			i;

	i = 0;
	get_params_len(params, 3, *((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 14);
	get_params_data(params, 3, ((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	addr = (params[0].value + params[1].value);
	*(REG_CAST *)proc->reg[params[2].value] = ((unsigned char *)e->arena)[*(REG_CAST *)proc->pc + addr];
	proc->carry = addr == 0 ? 1 : 0;
	len = full_len_size(op_tab[13].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** LFORK 0x0F
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle aussi
*/

void	op_lfork(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;
	int			i;

	i = 0;
	get_params_len(params, 1, *((unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 15);
	get_params_data(params, 1, ((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	if (params[0].value != 0)
		proc->next = new_proc(proc, params[0].value, 1);
	len = full_len_size(op_tab[14].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}
