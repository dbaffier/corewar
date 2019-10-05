/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations6_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:51:30 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/05 19:43:49 by gbourgeo         ###   ########.fr       */
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

void	op_and(t_param *params, t_process *proc, t_env *e)
{
	int			len;

	len = 0;
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		if (params[1].value > 0 && params[1].value < REG_NUMBER)
			if (params[2].value > 0 && params[2].value < REG_NUMBER)
			{
				len = *(REG_CAST *)proc->reg[params[0].value - 1] &
				*(REG_CAST *)proc->reg[params[1].value - 1];
				*(REG_CAST *)proc->reg[params[2].value - 1] = len;
			}
	proc->carry = (len == 0) ? 1 : 0;
	len = full_len_size(op_tab[5].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** OR 0x07
** OR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_or(t_param *params, t_process *proc, t_env *e)
{
	int			len;

	len = 0;
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		if (params[1].value > 0 && params[1].value < REG_NUMBER)
			if (params[2].value > 0 && params[2].value < REG_NUMBER)
			{
				len = *(REG_CAST *)proc->reg[params[0].value - 1] |
				*(REG_CAST *)proc->reg[params[1].value - 1];
				*(REG_CAST *)proc->reg[params[2].value - 1] = len;
			}
	proc->carry = (len == 0) ? 1 : 0;
	len = full_len_size(op_tab[6].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** XOR 0x08
** XOR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_xor(t_param *params, t_process *proc, t_env *e)
{
	int			len;

	len = 0;
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		if (params[1].value > 0 && params[1].value < REG_NUMBER)
			if (params[2].value > 0 && params[2].value < REG_NUMBER)
			{
				len = *(REG_CAST *)proc->reg[params[0].value - 1] ^
				*(REG_CAST *)proc->reg[params[1].value - 1];
				*(REG_CAST *)proc->reg[params[2].value - 1] = len;
			}
	proc->carry = (len == 0) ? 1 : 0;
	len = full_len_size(op_tab[7].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** ZJMP 0x09
** jump a l'adresse donnee en parametre si le carry est a un, sinon fail
*/

void	op_zjmp(t_param *params, t_process *proc, t_env *e)
{
	int			len;

	len = 3;
	if (proc->carry == 1)
		len = params[0].value;
	move_process_pc(proc, len, e);
}

/*
** LDI 0x0A
** additione les deux premiers param et va chercher a l'adresse de
** l'addition la valeur a ajouter dans le registre passé en 3eme parametre
** si l'addition = 0 le carry passe a 1
*/

void	op_ldi(t_param *params, t_process *proc, t_env *e)
{
	int			addr;
	int			len;

	addr = (params[0].value + params[1].value) % IDX_MOD;
	proc->carry = addr == 0 ? 1 : 0;
	if (params[2].value > 0 && params[2].value < REG_NUMBER)
	{
		addr = calc_mod(*(REG_CAST *)proc->pc + addr, MEM_SIZE);
		*(REG_CAST *)proc->reg[params[2].value - 1] =
			arena_get(e->arena, addr, REG_SIZE);
	}
	len = full_len_size(op_tab[9].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}
