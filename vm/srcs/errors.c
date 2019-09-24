/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:12:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/22 22:09:28 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

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
}

int				corewar_errors(int errnb, char *arg, t_env *e)
{
	static char	*error[] = {
		NULL,
		"value must contains only numbers",
		"value must be strictly positive",
		"unknown parameter",
		"invalid filename",
		"too many champions received",
		"number already taken",
		"missing champion",
		"impossible to open file",
		"impossible to lseek file for",
		"malloc failed for",
		"read failed for",
		"invalid champion: size too small for",
		"invalid champion: invalid header for",
		"invalid champion: champion size differ from header for",
		"invalid champion: size too big for",
	};

	ft_dprintf(2, "%s: %s", e->progname, error[errnb]);
	if (arg)
		ft_dprintf(2, " `%s'", arg);
	ft_dprintf(2, "\n");
	free_env(e);
	return (1);
}
