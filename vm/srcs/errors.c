/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:12:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/08 05:09:37 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

static void		corewar_usage(char *progname)
{
	ft_dprintf(2, "Usage : %s ", progname);
	ft_dprintf(2, "[-dump nbr_cycles] [[-n number] champion1.cor] ...\n\n");
	ft_dprintf(2, "\t-dump nbr_cycles\t: ");
	ft_dprintf(2, "Dumps memory after 'nbr_cycles' cycles then exits.\n");
	ft_dprintf(2, "\t-n number\t\t: ");
	ft_dprintf(2, "Fix a number to player. If missing, the player will ");
	ft_dprintf(2, "have the first available number.\n");
}

static void		corewar_print_error(const char *str, char *arg, char *progname)
{
	ft_dprintf(2, "%s: %s", progname, str);
	if (arg && str[ft_strlen(str) - 1] != '\t')
		ft_dprintf(2, " `%s'", arg);
	ft_dprintf(2, "\n");
	if (*str == '-')
		corewar_usage(progname);
}

void			corewar_errors(int errnb, char *arg, t_env *e)
{
	static const char	*error[] = {
		"-- missing argument.\t", "-- unknown argument", "-- help\t",
		"value must contain only numbers", "wrong value",
		"invalid filename", "too many champions received",
		"number already taken", "-- missing champion.\t",
		"impossible to open file", "impossible to lseek file for",
		"malloc failed", "read failed",
		"champion: size too small for", "champion: invalid header for",
		"champion: champion size differ from header for",
		"champion: size too big for",
		"ncurses: Failed to init main Window.\t",
		"ncurses: Failed to init arena Window Box.\t",
		"ncurses: Failed to init arena Window.\t",
		"Failed to init info Window Box.\t", "Failed to init champ Window.\t",
		"Failed to init VM Window.\t", "Failed to init info Window.\t",
	};

	if (errnb > 0 && errnb <= (int)(sizeof(error) / sizeof(error[0])))
		corewar_print_error(error[errnb - 1], arg, e->progname);
}
