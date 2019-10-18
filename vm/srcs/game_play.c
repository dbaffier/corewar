/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_play.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:05:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/18 20:34:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		check_live_total(size_t nb_live, int *cycle, int *last, int nb)
{
	if (nb_live >= NBR_LIVE)
	{
		*last = nb - 1;
		if ((*cycle = *cycle - CYCLE_DELTA) < 0)
			*cycle = 0;
	}
}

static void		check_max_checks(int *checks, int *cycle, int *last, int nb)
{
	if (++(*checks) == MAX_CHECKS)
	{
		*last = nb - 1;
		if ((*cycle = *cycle - CYCLE_DELTA) < 0)
			*cycle = 0;
		*checks = 0;
	}
}

static size_t	check_players_alive(t_env *e)
{
	t_process	*proc;
	size_t		alive;

	alive = 0;
	proc = e->proc;
	while (proc)
	{
		if (!proc->is_alive)
		{
			update_aff_champion_dead(e, proc);
			proc = remove_proc(proc, &e->proc, e);
			continue ;
		}
		alive += proc->is_alive;
		proc->is_alive = 0;
		proc = proc->next;
	}
	check_live_total(alive, &e->cycle_to_die, &e->last_cycle_to_die, e->nb_cycles);
	check_max_checks(&e->checks, &e->cycle_to_die, &e->last_cycle_to_die, e->nb_cycles);
	update_aff_vminfo(e);
	return (alive);
}

int				play_game(t_env *e)
{
	t_process	*proc;

	if (e->dump_cycle == e->nb_cycles)
	{
		return (-3);
	}
	if ((e->nb_cycles - e->last_cycle_to_die)
	&& (e->nb_cycles - e->last_cycle_to_die) % e->cycle_to_die == 0)
		if (!check_players_alive(e))
			return (-2);
	proc = e->proc;
	while (proc)
	{
		proc->instruction_wait += player_instruction(proc, e);
		update_aff_arena(*(REG_CAST *)proc->pc, 1,
		(short[2]){0, proc->color[1]}, e);
		proc = proc->next;
	}
	return (0);
}
