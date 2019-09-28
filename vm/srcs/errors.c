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

int				corewar_errors(int errnb, char *arg, t_env *e)
{
	static char	*error[] = {
		NULL,
		"-- help\t",
		"value must contains only numbers",
		"value must be strictly positive",
		"unknown parameter",
		"invalid filename",
		"too many champions received",
		"number already taken",
		"missing champion.\t",
		"impossible to open file",
		"impossible to lseek file for",
		"malloc failed for",
		"read failed for",
		"invalid champion: size too small for",
		"invalid champion: invalid header for",
		"invalid champion: champion size differ from header for",
		"invalid champion: size too big for",
		"ncurses: Failed to init main Window.\t",
		"ncurses: Failed to init arena Window Box.\t",
		"ncurses: Failed to init arena Window.\t",
		"Failed to init info Window Box.\t",
		"Failed to init champ Window.\t",
		"Failed to init VM Window.\t",
		"Failed to init info Window.\t",
	};

	ft_dprintf(2, "%s: %s", e->progname, error[errnb]);
	if (error[errnb][ft_strlen(error[errnb]) - 1] != '\t')
		ft_dprintf(2, " `%s'", arg);
	ft_dprintf(2, "\n");
	free_env(e);
	return (1);
}
