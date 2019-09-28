/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:22:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/27 00:34:48 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

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
			proc = remove_player(proc, &e->proc);
		else
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

	// if (e->ncu.infoWin)
	// 	wprintw(e->ncu.infoWin, "cycle: %ld (%d)\twait: %ld instruction: 0x%02X\n", nb_cycles, proc->id, proc->instruction_wait, proc->instruction);
	if (proc->instruction_wait != nb_cycles)
		return (0);
	if (proc->instruction_wait == nb_cycles)
	{
		if (proc->instruction == 0)
		{
			proc->instruction = *((unsigned char *)e->arena + *(REG_CAST *)proc->pc);
			if (proc->instruction > 0 && (proc->instruction < (unsigned char)(sizeof(op_tab) / sizeof(op_tab[0]))))
			{
				if (e->ncu.infoWin)
					wprintw(e->ncu.infoWin, "Player %d waiting %d cycle\n", proc->id, op_tab[proc->instruction - 1].cycle);
				proc->instruction_wait += op_tab[proc->instruction - 1].cycle;
			}
			else
			{
				move_process_pc(proc, 1, e);
				proc->instruction = 0;
			}
		}
		else
		{
			instruction_function[proc->instruction](proc, e);
			proc->instruction = 0;
		}
	}
	return (1);
}

static int		check_options(size_t nb_cycles, t_env *e)
{
	t_process	*proc;

	if (e->dump_cycle > -1 && (size_t)e->dump_cycle == nb_cycles)
	{
		dump_map(e->arena, MEM_SIZE);
		return (-1);
	}
	if ((nb_cycles + 1) % e->cycle_to_die == 0)
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

static void		and_the_winner_is(WINDOW *infoWin, t_live *live)
{
	if (infoWin)
	{
		if (live->last_id)
			wprintw(infoWin, "Le joueur %d(%s) a gagne\n", live->last_id, live->last_name);
		else
			wprintw(infoWin, "Aucun champion n'a gagne... Vraiment !?\n");
		nodelay(infoWin, FALSE);
		while (wgetch(infoWin) != 'q')
			wprintw(infoWin, "Press 'q' to quit...\n");
		return ;
	}
	if (live->last_id)
		ft_printf("Le joueur %d(%s) a gagne\n", live->last_id, live->last_name);
	else
		ft_printf("Aucun champion n'a gagne... Vraiment !?\n");
}

void			launch_game(t_env *e)
{
	size_t		nb_cycles;
	int			ch;

	nb_cycles = 0;
	ch = 0;
	e->pause = 1;
	while (1)
	{
		if (e->ncu.infoWin)
		{
			ncurses_affVMInfo(e, nb_cycles);
			if ((ch = ncurses_wgetch(&e->pause, e->ncu.infoWin)) == ERR)
				return ;
			else if (ch == 0)
				continue ;
		}
		if ((ch = check_options(nb_cycles, e)) != 0)
			break ;
		nb_cycles++;
	}
	if (ch == -2)
		and_the_winner_is(e->ncu.infoWin, &e->live);
}
