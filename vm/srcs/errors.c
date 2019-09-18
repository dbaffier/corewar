/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:12:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/18 18:40:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

void		free_env(t_env *e)
{
	int		i;

	i = 0;
	while (i < e->nb_players)
	{
		if (e->proc[i].data)
			free(e->proc[i].data);
		e->proc[i].data = NULL;
		i++;
	}
}

int			corewar_errors(int errnb, char *arg, t_env *e)
{
	static char	*error[] = {
		NULL,
		"value must contains only numbers",
		"value must be strictly positive",
		"unknown parameter",
		"invalid filename",
		"too many champions received",
		"number already taken",
		"missing champion.",
		"impossible to open file",
		"impossible to get file size for",
		"malloc failed for",
		"read failed for",
	};

	ft_dprintf(2, "%s: %s", e->progname, error[errnb]);
	if (arg)
		ft_dprintf(2, " `%s'", arg);
	ft_dprintf(2, "\n");
	free_env(e);
	return (1);
}
