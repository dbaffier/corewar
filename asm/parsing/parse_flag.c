/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:17:34 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 23:48:32 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		print_usage(int error)
{
	(void)error;
	ft_dprintf(2, "usage: ./asm [-Pnop] [file ...]\n");
	exit(0);
}

static int			set_msk(t_data *data, char c)
{
	static t_flags	tab[4] = {DASH_N, DASH_O, DASH_P, DASH_GP};
	size_t			i;

	i = 0;
	while (i < sizeof(tab) / sizeof(tab[i]))
	{
		if (c == tab[i].opt)
		{
			data->flag |= tab[i].msk;
			return (1);
		}
		i++;
	}
	return (0);
}

int			parse_flag(t_data *data, char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' && av[i][j + 1] == '-')
				return (0);
			if (j == 0 && av[i][j] != '-')
				return (ERR_FLAG);
			if (j != 0 && av[i][j] == '-')
				return (ERR_FLAG);
			if (av[i][j] != '-')
				if (set_msk(data, av[i][j]) == 0)
					return (ERR_FLAG);
			j++;
		}
		i++;
	}
	return (0);
}
