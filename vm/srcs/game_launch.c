/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:48:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/29 21:48:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

static void		print_win_str(t_ncurse *ncu, t_live *live)
{
	char		*str;
	char		*quit;
	int			len;
	int			x;
	int			y;

	str = (live->last_id) ? "Le joueur %d(%s) a gagné !" : "Aucun champion n'a gagné.";
	quit = "Press 'q' to quit...";
	len = ft_strlen(str);
	if (live->last_id)
		len += ft_strlen(live->last_name);
	x = (len > ncu->winx) ? 0 : ncu->winx / 2 - len / 2;
	y = (3 > ncu->winy) ? 0 : ncu->winy / 2 - 1;
	mvwprintw(ncu->infoWin, y, x, str, live->last_id, live->last_name);
	len = ft_strlen(quit);
	x = (len > ncu->winx) ? 0 : ncu->winx / 2 - len / 2;
	if (ncu->winy <= 1)
		y = -1;
	else
		y = (ncu->winy == 2) ? 0 : ncu->winy / 2 + 1;
	mvwprintw(ncu->infoWin, y, x, quit);
}

static void		and_the_winner_is(t_ncurse *ncu, t_live *live) // MC HAMMER
{
	if (ncu->infoWin)
	{
		wclear(ncu->infoWin);
		wattron(ncu->infoWin, A_BOLD);
		wbkgd(ncu->infoWin, COLOR_PAIR(COREWAR_WINNER_COLOR));
		print_win_str(ncu, live);
		wrefresh(ncu->infoWin);
		nodelay(ncu->infoWin, FALSE);
		while (wgetch(ncu->infoWin) != 'q')
			print_win_str(ncu, live);
		return ;
	}
	if (live->last_id)
		ft_printf("Le joueur %d(%s) a gagné\n", live->last_id, live->last_name);
	else
		ft_printf("Aucun champion n'a gagné.\n");
}

void			launch_game(t_env *e)
{
	size_t		nb_cycles;
	int			ch;

	nb_cycles = 0;
	ch = 0;
	e->pause = 1;
	e->speed = VM_SPEED_INIT;
	e->cycle_to_die = CYCLE_TO_DIE;
	ncurses_affAll(e);
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
		and_the_winner_is(&e->ncu, &e->live);
}
