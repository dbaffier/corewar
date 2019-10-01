/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:42:45 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/01 19:47:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

extern struct s_op	op_tab[17];

/*
** LIVE 0x01
** renvoie un live pour le processus qui l'appelle
*/

void	op_live(t_process *proc, t_env *e)
{
	uint8_t		*arena;
	t_param		params[3];
	t_process	*tail;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 1, *(arena + *(REG_CAST *)proc->pc + 1), 1);
	get_params_data(params, 1, arena + *(REG_CAST *)proc->pc);
	tail = e->proc;
	while (tail)
	{
		if (params[0].value == tail->id)
		{
			tail->is_alive++;
			e->live.last_id = params[0].value;
			ft_strncpy(e->live.name, ((t_header *)tail->file)->prog_name,
							PROG_NAME_LENGTH + 1);
			break ;
		}
		tail = tail->next;
	}
	print_live(e, params, tail);
	proc->is_alive++;
	move_process_pc(proc, 5, e);
}

/*
** DIRECT_LOAD 0x02
** load le 1er parametre dans le registre passé en 2nd parametre
** si le 1st param = 0 le carry passe a 1
*/

void	op_ld(t_process *proc, t_env *e)
{
	uint8_t		*arena;
	t_param		params[3];
	int			len;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 2, *(arena + *(REG_CAST *)proc->pc + 1), 2);
	get_params_data(params, 2, arena + *(REG_CAST *)proc->pc);
	if (params[1].value > 0 && params[1].value < REG_NUMBER)
	{
		if (params[0].size == 2)
		{
			*(REG_CAST *)proc->reg[params[1].value - 1]
			= *(REG_CAST *)((int8_t *)e->arena + calc_mod(*(REG_CAST *)proc->pc
			+ ((short)params[0].value % IDX_MOD), MEM_SIZE));
			*(REG_CAST *)proc->reg[params[1].value - 1]
			= byteswap_32(*(REG_CAST *)proc->reg[params[1].value - 1]);
		}
		else if (params[0].size == 4)
		{
			*(REG_CAST *)proc->reg[params[1].value - 1] = params[0].value;
		}
	}
	proc->carry = (params[0].value == 0) ? 1 : 0;
	len = full_len_size(op_tab[1].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** DIRECT STORE 0x03
** inverse de load charge le registre passe en 1st param dans le 2nd param
** meme fonctionnement pour le carry
*/

void	op_st(t_process *proc, t_env *e)
{
	uint8_t		*arena;
	t_param		params[3];
	int			len;

	arena = (uint8_t *)e->arena;
	get_params_len(params, 2, *(arena + *(REG_CAST *)proc->pc + 1), 3);
	get_params_data(params, 2, arena + *(REG_CAST *)proc->pc);
	if (params[0].value > 0 && params[0].value < REG_NUMBER)
		handle_st(params, proc, e);
	len = full_len_size(op_tab[2].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** ADD 0x04
** ajoute le 1er param et le 2nd et stocke le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_add(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;

	get_params_len(params, 3, *((uint8_t *)e->arena +
		*(REG_CAST *)proc->pc + 1), 4);
	get_params_data(params, 3, ((uint8_t *)e->arena) +
		*(REG_CAST *)proc->pc);
	*(REG_CAST *)proc->reg[params[2].value] = params[0].value +
		params[1].value;
	proc->carry = params[0].value + params[1].value == 0 ? 1 : 0;
	len = full_len_size(op_tab[3].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}

/*
** SUB 0x05
** soustraie le 1er param et le 2nd et stocke le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

void	op_sub(t_process *proc, t_env *e)
{
	t_param		params[3];
	int			len;

	get_params_len(params, 3,
			*((uint8_t *)e->arena + *(REG_CAST *)proc->pc + 1), 5);
	get_params_data(params, 3,
			(uint8_t *)e->arena + *(REG_CAST *)proc->pc);
	*(REG_CAST *)proc->reg[params[2].value] = params[0].value -
		params[1].value;
	proc->carry = params[0].value - params[1].value == 0 ? 1 : 0;
	len = full_len_size(op_tab[4].reg_nb, params);
	move_process_pc(proc, len + 2, e);
}
