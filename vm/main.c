 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:05:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/17 18:05:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static int		usage(char *progname)
{
	ft_dprintf(2, "Usage :\n%s", progname);
	ft_dprintf(2, "[-dump nbr_cycles] [[-n number] champion1.cor] ...]\n");
	return (1);
}

void			get_args(char **av, t_env *e)
{
	int				i;
	char			*tmp;
	int				n;

	i = 0;
	while (av[i])
	{
		if (ft_strequ(av[i], "-dump"))
		{
			
		}
		else if (ft_strequ(av[i], "-n"))
		{
			n = ft_atoi(av[i + 1]);
			if (ft_isdigit(n) && n > 0 && n < MAX_PLAYERS)
				e->n = n;
		}
		else if ((tmp = ft_strrchr(av[i], '.')) && ft_strequ(tmp, ".cor"))
		{

		}
		else if (av[i][0] == '-')
			return (ft_dprintf(2, "%s: wrong parameter.\n", av[i]));
		else
			return (ft_dprintf(2, "%s: wrong champion filename.\n", av[i]));
		i++;
	}
}

int				main(int ac, char **av)
{
	t_env	e;

	ft_memset(&env, 0, sizeof(e));
	if (ac < 3)
		return (usage(av[0]));
	get_args(av, &e);
	return (42);
}
