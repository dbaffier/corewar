/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:05:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/18 03:00:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "ft_printf.h"

static int		usage(char *progname)
{
	ft_dprintf(2, "Usage :\n%s ", progname);
	ft_dprintf(2, "[-dump nbr_cycles] [-n number [1-4] champion1.cor] ...]\n");
	return (1);
}

int				main(int ac, char **av)
{
	t_env	e;

	ft_memset(&e, 0, sizeof(e));
	if (!(e.progname = ft_strrchr(av[0], '/')))
		e.progname = av[0];
	if (ac < 3 || get_args(av, &e))
		return (usage(av[0]));
	return (42);
}
