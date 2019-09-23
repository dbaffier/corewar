/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 22:02:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/21 01:04:21 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

static void			check_players_alive(t_process *proc, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (!proc[i].is_alive)
		{
			if (proc[i].is_dead == 0)
				system("afplay ~/Desktop/roblox-death-sound-effect.mp3");
			proc[i].is_dead = 1;
		}
		i++;
	}
}

void			launch_game(t_env *e)
{
	int		i;
	int		nb_cycles;

	nb_cycles = 0;
	while (0)
	{
		if (nb_cycles == CYCLE_TO_DIE)
			check_players_alive(e->proc, e->nb_players);
		i = e->nb_players;
		while (i--)
		{

		}
	}
}
