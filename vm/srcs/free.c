/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 00:34:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/08 04:47:35 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

static void		free_proc(t_process *proc)
{
	t_process	*next;

	while (proc)
	{
		next = proc->next;
		if (proc->file && --proc->free_file[proc->pos] == 0)
			free((proc)->file);
		free(proc);
		proc = next;
	}
}

void			free_env(t_env *e)
{
	free_proc(e->proc);
	if (e->arena)
		free(e->arena);
	if (e->colors)
		free(e->colors);
}
