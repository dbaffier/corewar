/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_play.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:05:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 02:31:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern t_op op_tab[17];

static void			check_live_total(t_live *live, int *cycle_to_die)
{
	if (live->total == NBR_LIVE)
		if ((*cycle_to_die = *cycle_to_die - CYCLE_DELTA) < 0)
			*cycle_to_die = 0;
	live->total = 0;
}

static void			check_max_checks(int *checks, int *cycle_to_die)
{
	if (++(*checks) == MAX_CHECKS)
	{
		if ((*cycle_to_die = *cycle_to_die - CYCLE_DELTA) < 0)
			*cycle_to_die = 0;
		*checks = 0;
	}
}

static int			check_players_alive(t_env *e)
{
	t_process	*proc;
	int			alive;

	alive = 0;
	proc = e->proc;
	while (proc)
	{
		alive += proc->is_alive;
		if (!proc->is_alive)
		{
			proc = remove_player(proc, &e->proc);
			ncurses_affChampion(e);
			e->nb_players--;
			continue ;
		}
		proc->is_alive = 0;
		proc = proc->next;
	}
	check_live_total(&e->live, &e->cycle_to_die);
	check_max_checks(&e->checks, &e->cycle_to_die);
	return (alive);
}

static size_t	player_instruction(t_process *proc, t_env *e, size_t nb_cycles)
{
	static void	(*instruction_function[])(t_process *, t_env *) = {
		NULL, op_live, op_ld, op_st, op_add, op_sub, op_and, op_or, op_xor,
		op_zjmp, op_ldi, op_sti, op_fork, op_lld, op_lldi, op_lfork, op_aff,
	};

	if (proc->instruction_wait != nb_cycles)
		return (0);
	if (proc->instruction_wait == nb_cycles)
	{
		if (proc->instruction == 0)
		{
			proc->instruction = *((unsigned char *)e->arena + *(REG_CAST *)proc->pc);
			if (proc->instruction > 0 && (proc->instruction < (unsigned char)(sizeof(op_tab) / sizeof(op_tab[0]))))
			{
				// if (e->ncu.infoWin)
				// 	wprintw(e->ncu.infoWin, "Player %d waiting %d cycle\n", proc->id, op_tab[proc->instruction - 1].cycle);
				return (op_tab[proc->instruction - 1].cycle - 1);
			}
			else
				move_process_pc(proc, 1, e);
		}
		else
			instruction_function[proc->instruction](proc, e);
		proc->instruction = 0;
	}
	return (1);
}

int				play_game(size_t nb_cycles, t_env *e)
{
	t_process	*proc;

	if (e->dump_cycle > -1 && (size_t)e->dump_cycle == nb_cycles)
	{
		if (!e->ncu.mainWin)
			dump_map(e->arena, MEM_SIZE);
		return (-1);
	}
	if (nb_cycles && nb_cycles % e->cycle_to_die == 0)
		if (!check_players_alive(e))
			return (-2) ;
	proc = e->proc;
	while (proc)
	{
		proc->instruction_wait += player_instruction(proc, e, nb_cycles);
		proc = proc->next;
	}
	return (0);
}
