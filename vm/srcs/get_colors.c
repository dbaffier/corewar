/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:10:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 23:33:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

static void		fill_colors(short *colors, short color, int size)
{
	int			i;

	i = 0;
	while (i < size)
		colors[i++] = color;
}

int				get_colors(t_env *e)
{
	t_process	*proc;

	proc = e->proc;
	if (!e->ncu.main_win)
		return (IS_OK);
	if ((e->colors = malloc(MEM_SIZE * sizeof(*e->colors))) == NULL)
		return (corewar_errors(ERR_MALLOC, NULL, e));
	fill_colors(e->colors, 1, MEM_SIZE);
	while (proc)
	{
		fill_colors(e->colors + *(REG_CAST *)proc->pc, proc->color[0],
		proc->data_size);
		proc = proc->next;
	}
	return (IS_OK);
}
