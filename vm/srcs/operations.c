/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:42:45 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/19 18:30:48 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

// DIRECT_LOAD

void	op_dl(t_process *proc, )
{
	// get in data le 1st param et le load dans le registre en 2nd param
	// si le 1st param = 0 le carry passe a 1
	int		firstparam;
	char	registre[REG_SIZE];

	firstparam = get_param(proc->data, 1);
	registre = get_reg_data(proc->data, 2);
	e->arena= load_data(firstparam, (int)registre);
	proc->carry = firstparam == 0 ? 1 : 0;
}

// DIRECT STORE

void	op_ds(t_process *proc)
{
	// inverse de load charge le registre passe en 1st param dans le 2nd param
	// meme fonctionnement pour le carry
	int		secondparam;
	char	registre[REG_SIZE];

	registre = get_reg_data(proc->data, 1);
	secondparam = get_param(proc->data, 2);
	proc->data = load_data((int)registre, secondparam);
	proc->carry = firstparam == 0 ? 1 : 0;
}
