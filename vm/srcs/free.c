/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 00:34:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/29 21:04:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

static void		free_proc(t_process **proc)
{
	if (proc)
		if (*proc)
		{
			free_proc(&(*proc)->next);
			if ((*proc)->file)
				free((*proc)->file);
			free(*proc);
			*proc = NULL;
		}
}

void			free_env(t_env *e)
{
	free_proc(&e->proc);
	if (e->arena)
		free(e->arena);
	if (e->colors)
		free(e->colors);
}
