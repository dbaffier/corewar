/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:42:45 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/20 04:13:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

// DIRECT_LOAD

<<<<<<< HEAD
void	op_ld(t_process *proc, unsigned char *arena, t_op *op)
=======
void	op_dl(t_process *proc, t_env *e, t_op *op)
>>>>>>> afa722a543a775a2b29bf12c5ebb69e85f5b3c1f
{
	// get in data le 1st param et le load dans le registre en 2nd param
	// si le 1st param = 0 le carry passe a 1
	char	registre[REG_SIZE];

<<<<<<< HEAD
	firstparam = get_param(proc->file, 1, op);
	registre = get_reg_data(proc->file, 2, op);
	e->arena = load_data(firstparam, (int)registre);
=======
	get_params_len(op->arg_type, 2);
	params = get_params_data(op, params, 2);
	registre = get_reg_data(o, params, 2, (char *)proc->file);
	e->arena= load_data(firstparam, (int)registre);
>>>>>>> afa722a543a775a2b29bf12c5ebb69e85f5b3c1f
	proc->carry = firstparam == 0 ? 1 : 0;
}

// DIRECT STORE

void	op_st(t_process *proc)
{
	// inverse de load charge le registre passe en 1st param dans le 2nd param
	// meme fonctionnement pour le carry
	int		secondparam;
	char	registre[REG_SIZE];

	registre = get_reg_data(proc->file, 1) op_tab[];
	secondparam = get_param(proc->file, 2);
	proc->file = load_data((int)registre, secondparam);
	proc->carry = firstparam == 0 ? 1 : 0;
}
