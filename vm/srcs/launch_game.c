/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:12:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/28 23:12:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void		and_the_winner_is(WINDOW *infoWin, t_live *live)
{
	if (infoWin)
	{
		if (live->last_id)
			wprintw(infoWin, "Le joueur %d(%s) a gagne\n",
			live->last_id, live->last_name);
		else
			wprintw(infoWin, "Aucun champion n'a gagne... Vraiment !?\n");
		nodelay(infoWin, FALSE);
		while (wgetch(infoWin) != 'q')
			wprintw(infoWin, "Press 'q' to quit...\n");
		return ;
	}
	if (live->last_id)
		ft_printf("Le joueur %d(%s) gagne\n", live->last_id, live->last_name);
	else
		ft_printf("Aucun champion ne gagne... Vraiment !?\n");
}

void			launch_game(t_env *e)
{
	size_t		nb_cycles;
	int			ch;

	nb_cycles = 0;
	ch = 0;
	e->pause = 1;
	e->speed = VM_SPEED_INIT;
	while (1)
	{
		if (e->ncu.infoWin)
		{
			update_affVMInfo(e, nb_cycles);
			if ((ch = ncurses_wgetch(&e->speed, &e->pause, e->ncu.infoWin)) == ERR)
				return ;
			else if (ch == 0)
				continue ;
		}
		if ((ch = play_game(nb_cycles, e)) != 0)
			break ;
		nb_cycles++;
	}
	if (ch == -2)
		and_the_winner_is(e->ncu.infoWin, &e->live);
}
