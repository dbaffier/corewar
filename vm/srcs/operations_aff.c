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

/*
** AFF 0x10
** Affiche le char qui est donne en 1er param si il est nul carry = 1
*/

void	op_aff(t_process *proc, t_env *e)
{
	t_param		params[3];

	get_params_len(params, 1, (*(unsigned char *)e->arena + *(REG_CAST *)proc->pc + 1), 1);
	get_params_data(params, 1, ((unsigned char *)e->arena) + *(REG_CAST *)proc->pc, *(REG_CAST *)proc->pc);
	ft_printf("corewar : [%s] : \"%c\"\n", proc->file_name, params[0].value);
	proc->carry = params[0].value == 0 ? 1 : 0;
}