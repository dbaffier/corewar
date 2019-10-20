/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:12:05 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/19 19:27:32 by gbourgeo         ###   ########.fr       */
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

int		op_sti(t_param *params, t_process *proc, t_env *e)
{
	int		offset;

	if (params[1].type == REG_CODE)
		offset = *(REG_CAST *)proc->reg[params[1].value - 1];
	else if (params[1].type == DIR_CODE)
		offset = params[1].value;
	else
		offset = arena_get(e->arena, *(REG_CAST *)proc->pc + params[1].value);
	if (params[2].type == REG_CODE)
		offset += *(REG_CAST *)proc->reg[params[2].value - 1];
	else if (params[2].type == DIR_CODE)
		offset += params[2].value;
	offset = *(REG_CAST *)proc->pc + ((short)offset % IDX_MOD);
	arena_copy(offset, (REG_CAST *)proc->reg[params[0].value - 1],
		proc->color[0], e);
	return (!proc->carry);
}

/*
** FORK 0x0C
** Cree un nouveau processus
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle du coup
*/

int		op_fork(t_param *params, t_process *proc, t_env *e)
{
	if (params[0].value != 0)
		new_proc(proc, params[0].value, 0, e);
	return (!proc->carry);
}

/*
** LLD 0x0D
** direct load sans le %IDX_MOD
** si le 1st param = 0 le carry passe a 1
*/

int		op_lld(t_param *params, t_process *proc, t_env *e)
{
	if (params[0].type == DIR_CODE)
		*(REG_CAST *)proc->reg[params[1].value - 1] = params[0].value;
	else if (params[0].type == IND_CODE)
	{
		params[0].value = *(REG_CAST *)proc->pc + params[0].value;
		*(REG_CAST *)proc->reg[params[1].value - 1] =
		arena_get(e->arena, params[0].value);
	}
	return (*(REG_CAST *)proc->reg[params[1].value - 1]);
}

/*
** LLDI 0x0E
** ldi sans restriction d'adressage
** si l'addition = 0 le carry passe a 1
*/

int		op_lldi(t_param *params, t_process *proc, t_env *e)
{
	int			ret;
	int			offset;

	if (params[0].type == REG_CODE)
		ret = *(REG_CAST *)proc->reg[params[0].value - 1];
	else if (params[0].type == DIR_CODE)
		ret = params[0].value;
	else
		ret = arena_get(e->arena, *(REG_CAST *)proc->pc + params[0].value);
	if (params[1].type == REG_CODE)
		ret += *(REG_CAST *)proc->reg[params[1].value - 1];
	else
		ret += params[1].value;
	offset = *(REG_CAST *)proc->pc + ret;
	*(REG_CAST *)proc->reg[params[2].value - 1] = arena_get(e->arena, offset);
	return (*(REG_CAST *)proc->reg[params[2].value - 1]);
}

/*
** LFORK 0x0F
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle aussi
*/

int		op_lfork(t_param *params, t_process *proc, t_env *e)
{
	if (params[0].value != 0)
		proc->prev = new_proc(proc, params[0].value, 1, e);
	return (!proc->carry);
}
