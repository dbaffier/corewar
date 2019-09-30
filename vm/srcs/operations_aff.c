/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:23:33 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/23 02:29:00 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

extern t_op op_tab[17];

/*
** AFF 0x10
** Affiche le char qui est donne en 1er param si il est nul carry = 1
*/

void	op_aff(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;
	int 		i;

	i = 0;
	get_params_len(params, 1,
		(*(unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 1);
	get_params_data(params, 1,
		((unsigned char *)e->arena) + *(REG_CAST *)proc->pc);
	if (e->ncu.infoWin)
		wprintw(e->ncu.infoWin, "corewar : [%s] : \"%c\"\n",
			((t_header *)proc->file)->prog_name, params[0].value);
	else
		ft_printf("corewar : [%s] : \"%c\"\n", 
			((t_header *)proc->file)->prog_name, params[0].value);
	proc->carry = params[0].value == 0 ? 1 : 0;
	len = full_len_size(op_tab[15].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

void	print_live(t_env *e, t_param *params, t_process *tail)
{
	if (e->ncu.infoWin)
		wprintw(e->ncu.infoWin, "%s: un processus dit que le joueur %d(%s)
			est en vie\n",
			e->progname, params[0].value, (tail) ?
				((t_header *)tail->file)->prog_name : "?");
	else
		ft_printf("%s: un processus dit que le joueur %d(%s) est en vie\n",
			e->progname, params[0].value, (tail) ?
				((t_header *)tail->file)->prog_name : "?");
}