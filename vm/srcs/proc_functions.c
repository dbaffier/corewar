/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:45:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/20 23:38:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void		update_aff_processes(t_process *proc, t_env *e)
{
	int			i;
	int			total;
	int			color;

	i = 0;
	total = 0;
	color = A_BOLD | COLOR_PAIR(COREWAR_CHAMPWIN_COLOR);
	if (e->ncu.champ_win)
	{
		wattron(e->ncu.champ_win, color);
		wmove(e->ncu.champ_win, proc->pos_y + 2, 0);
		wclrtoeol(e->ncu.champ_win);
		mvwprintw(e->ncu.champ_win, proc->pos_y + 2, 0, "Processes: %d",
		*proc->free_file);
		while (i < MAX_PLAYERS)
			total += e->free_file[i++];
		i = e->ncu.winy - 1;
		wmove(e->ncu.champ_win, i, 0);
		wclrtoeol(e->ncu.champ_win);
		mvwprintw(e->ncu.champ_win, i, 0, "Processes: %d", total);
		wattroff(e->ncu.champ_win, color);
		wrefresh(e->ncu.champ_win);
	}
}

t_process		*new_proc(t_process *proc, int value, int flag, t_env *e)
{
	t_process	*new;

	new = ft_memalloc(sizeof(*new));
	ft_memcpy(new, proc, sizeof(*new));
	(*new->free_file)++;
	new->instruction_wait += 1;
	new->instruction = 0;
	if (!flag)
		move_process_pc(new, ((short)value % IDX_MOD), e);
	else
		move_process_pc(new, value, e);
	while (proc->prev && proc->prev->id == proc->id)
		proc = proc->prev;
	new->next = proc;
	if ((new->prev = proc->prev) != NULL)
		new->prev->next = new;
	else
		e->proc = new;
	proc->prev = new;
	update_aff_processes(proc, e);
	return (new);
}

t_process		*remove_proc(t_process *proc, t_env *e)
{
	t_process	*next;

	next = proc->next;
	if (proc->prev)
		proc->prev->next = proc->next;
	else
		e->proc = proc->next;
	if (proc->next)
		proc->next->prev = proc->prev;
	if (proc->file && --(*proc->free_file) == 0)
		free(proc->file);
	update_aff_processes(proc, e);
	ft_bzero(proc, sizeof(*proc));
	free(proc);
	return (next);
}

/*
** system("afplay ~/Desktop/roblox-death-sound-effect.mp3 2>&-");
*/
