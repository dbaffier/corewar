/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:12:05 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/05 18:16:25 by gbourgeo         ###   ########.fr       */
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

void	op_sti(t_param *params, t_process *proc, t_env *e)
{
	int			len;

wprintw(e->ncu.info_win, "p[0]{%d, %d, %d}, ", params[0].size, params[0].value, params[0].type);
wprintw(e->ncu.info_win, "p[1]{%d, %d, %d}, ", params[1].size, params[1].value, params[1].type);
wprintw(e->ncu.info_win, "p[2]{%d, %d, %d}\n", params[2].size, params[2].value, params[2].type);
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		proc->carry = !handle_sti(params, proc, e);
	len = full_len_size(op_tab[10].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** FORK 0x0C
** Cree un nouveau processus
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle du coup
*/

void	op_fork(t_param *params, t_process *proc, t_env *e)
{
	int			len;

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

void	op_lld(t_param *params, t_process *proc, t_env *e)
{
	int			len;

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

void	op_lldi(t_param *params, t_process *proc, t_env *e)
{
	int			addr;
	int			len;

	addr = params[0].value + params[1].value;
	*(REG_CAST *)proc->reg[params[2].value] =
		((uint8_t *)e->arena)[*(REG_CAST *)proc->pc + addr];
	proc->carry = addr == 0 ? 1 : 0;
	len = full_len_size(op_tab[13].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** LFORK 0x0F
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle aussi
*/

void	op_lfork(t_param *params, t_process *proc, t_env *e)
{
	int			len;

	if (params[0].value != 0)
		proc->next = new_proc(proc, params[0].value, 1, e);
	len = full_len_size(op_tab[14].reg_nb, params);
	move_process_pc(proc, len + 1, e);
}
