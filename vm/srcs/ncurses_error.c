/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:23:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/25 16:24:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

int				ncurses_error(char *str, t_env *e)
{
	ncurses_end(e);
	ft_dprintf(2, "%s: ncurse: %s\n", e->progname, str);
	return (0);
}

