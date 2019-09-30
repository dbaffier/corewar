/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:12:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/30 23:31:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

static void		corewar_print_error(const char *str, char *arg, char *progname)
{
	ft_dprintf(2, "%s: %s", progname, str);
	if (str[ft_strlen(str) - 1] != '\t')
		ft_dprintf(2, " `%s'", arg);
	ft_dprintf(2, "\n");
}

int				corewar_errors(int errnb, char *arg, t_env *e)
{
	static const char	*error[] = {
		"-- help\t", "value must contains only numbers",
		"value must be strictly positive", "unknown parameter",
		"invalid filename", "too many champions received",
		"number already taken", "missing champion.\t",
		"impossible to open file", "impossible to lseek file for",
		"malloc failed for", "read failed for",
		"invalid champion: size too small for",
		"invalid champion: invalid header for",
		"invalid champion: champion size differ from header for",
		"invalid champion: size too big for",
		"ncurses: Failed to init main Window.\t",
		"ncurses: Failed to init arena Window Box.\t",
		"ncurses: Failed to init arena Window.\t",
		"Failed to init info Window Box.\t", "Failed to init champ Window.\t",
		"Failed to init VM Window.\t", "Failed to init info Window.\t",
	};

	--errnb;
	if (errnb < 0 || errnb > (int)(sizeof(error) / sizeof(error[0])))
		return (1);
	corewar_print_error(error[errnb], arg, e->progname);
	free_env(e);
	return (1);
}
