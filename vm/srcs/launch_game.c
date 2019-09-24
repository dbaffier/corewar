/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:22:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/23 21:22:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void			check_live_total(t_live *live, int *cycle_to_die)
{
	if (live->total == NBR_LIVE)
		if ((*cycle_to_die = *cycle_to_die - CYCLE_DELTA) < 0)
			*cycle_to_die = 0;
	ft_memset(live, 0, sizeof(*live));
}

static int			check_players_alive(t_process **head, t_env *e)
{
	t_process	*proc;
	int			alive;

	alive = 0;
	proc = *head;
	while (proc)
	{
		alive += proc->is_alive;
		if (!proc->is_alive)
		{
		}
		else
			proc = proc->next;
	}
	check_live_total(&e->live, &e->cycle_to_die);
	return (alive);
}

void			launch_game(t_env *e)
{
	t_process	*proc;
	size_t		nb_cycles;

	nb_cycles = 0;
	while (1)
	{
		proc = e->proc;
		if (e->dump_cycle > -1 && (size_t)e->dump_cycle == nb_cycles)
		{
			dump_map(e->arena, MEM_SIZE);
			return ;
		}
		if ((nb_cycles + 1) % e->cycle_to_die == 0)
			if (!check_players_alive(&e->proc, e))
				break ;
		nb_cycles++;
	}
}
