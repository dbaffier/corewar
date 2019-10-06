/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations6_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:51:30 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/06 19:35:19 by gbourgeo         ###   ########.fr       */
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

int		op_and(t_param *params, t_process *proc, t_env *e)
{
	int	and;

	and = 0;
	(void)e;
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		if (params[1].value > 0 && params[1].value < REG_NUMBER)
			if (params[2].value > 0 && params[2].value < REG_NUMBER)
			{
				and = *(REG_CAST *)proc->reg[params[0].value - 1] &
				*(REG_CAST *)proc->reg[params[1].value - 1];
				*(REG_CAST *)proc->reg[params[2].value - 1] = and;
			}
	return (and);
}

/*
** OR 0x07
** OR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

int		op_or(t_param *params, t_process *proc, t_env *e)
{
	int	or;

	or = 0;
	(void)e;
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		if (params[1].value > 0 && params[1].value < REG_NUMBER)
			if (params[2].value > 0 && params[2].value < REG_NUMBER)
			{
				or = *(REG_CAST *)proc->reg[params[0].value - 1] |
				*(REG_CAST *)proc->reg[params[1].value - 1];
				*(REG_CAST *)proc->reg[params[2].value - 1] = or;
			}
	return (or);
}

/*
** XOR 0x08
** XOR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

int		op_xor(t_param *params, t_process *proc, t_env *e)
{
	int	xor;

	xor = 0;
	(void)e;
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		if (params[1].value > 0 && params[1].value < REG_NUMBER)
			if (params[2].value > 0 && params[2].value < REG_NUMBER)
			{
				xor = *(REG_CAST *)proc->reg[params[0].value - 1] ^
				*(REG_CAST *)proc->reg[params[1].value - 1];
				*(REG_CAST *)proc->reg[params[2].value - 1] = xor;
			}
	return (xor);
}

/*
** ZJMP 0x09
** jump a l'adresse donnee en parametre si le carry est a un, sinon fail
*/

int		op_zjmp(t_param *params, t_process *proc, t_env *e)
{
	(void)e;
	if (proc->carry == 1)
		params[0].size = params[0].value - 1;
	return (0);
}

/*
** LDI 0x0A
** additione les deux premiers param et va chercher a l'adresse de
** l'addition la valeur a ajouter dans le registre passé en 3eme parametre
** si l'addition = 0 le carry passe a 1
*/

int		op_ldi(t_param *params, t_process *proc, t_env *e)
{
	int			addr;

	addr = 0;
	if (params[2].value > 0 && params[2].value < REG_NUMBER)
	{
		addr = (params[0].value + params[1].value) % IDX_MOD;
		addr = calc_mod(*(REG_CAST *)proc->pc + addr, MEM_SIZE);
		*(REG_CAST *)proc->reg[params[2].value - 1] =
			arena_get(e->arena, addr, REG_SIZE);
		addr = params[0].value + params[1].value;
	}
	return (addr);
}
