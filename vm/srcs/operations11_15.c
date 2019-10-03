/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:12:05 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/02 18:56:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

extern struct s_op	op_tab[17];

/*
** STI 0x0B
** additione les deux derniers param et va changer la valeur a l'adresse de
** l'addition avec la valeur dans le registre passé en 1eme parametre
** si l'addition = 0 le carry passe a 1
*/

void	op_sti(t_process *proc, t_env *e)
{
	uint8_t		*arena;
	t_param		params[3];
	int			len;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 3,
		*(arena + (*(REG_CAST *)proc->pc + 1) % MEM_SIZE), 11);
	get_params_data(params, 3, arena, *(REG_CAST *)proc->pc);
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		handle_sti(params, proc, e);
	len = full_len_size(op_tab[10].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** FORK 0x0C
** Cree un nouveau processus
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle du coup
*/

void	op_fork(t_process *proc, t_env *e)
{
	uint8_t		*arena;
	t_param		params[3];
	int			len;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 1,
		*(arena + (*(REG_CAST *)proc->pc + 1) % MEM_SIZE), 12);
	get_params_data(params, 1, arena, *(REG_CAST *)proc->pc);
	if (params[0].value != 0)
		proc->next = new_proc(proc, params[0].value, 0, e);
	len = full_len_size(op_tab[11].reg_nb, params);
	move_process_pc(proc, len + 1, e);
}

/*
** LLD 0x0D
** direct load sans le %IDX_MOD
** si le 1st param = 0 le carry passe a 1
*/

void	op_lld(t_process *proc, t_env *e)
{
	uint8_t		*arena;
	t_param		params[3];
	int			len;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 2,
		*(arena + (*(REG_CAST *)proc->pc + 1) % MEM_SIZE), 13);
	get_params_data(params, 2, arena, *(REG_CAST *)proc->pc);
	*(REG_CAST *)proc->reg[params[1].value] =
		*(REG_CAST *)proc->pc + (params[0].value % MEM_SIZE);
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
	uint8_t		*arena;
	t_param		params[3];
	int			addr;
	int			len;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 3,
		*(arena + (*(REG_CAST *)proc->pc + 1) % MEM_SIZE), 14);
	get_params_data(params, 3, arena, *(REG_CAST *)proc->pc);
	addr = params[0].value + params[1].value;
	*(REG_CAST *)proc->reg[params[2].value] = arena[*(REG_CAST *)proc->pc + addr];
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
	uint8_t		*arena;
	t_param		params[3];
	int			len;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 1,
		*(arena + (*(REG_CAST *)proc->pc + 1) % MEM_SIZE), 15);
	get_params_data(params, 1, arena, *(REG_CAST *)proc->pc);
	if (params[0].value != 0)
		proc->next = new_proc(proc, params[0].value, 1, e);
	len = full_len_size(op_tab[14].reg_nb, params);
	move_process_pc(proc, len + 1, e);
}
