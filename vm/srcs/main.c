/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:05:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/19 23:17:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

static int		usage(char *progname)
{
	ft_dprintf(2, "Usage :\n%s ", progname);
	ft_dprintf(2, "[-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	return (1);
}

static void		debug_champ(t_env *e)
{
	int			i;
	int			off;

	return ;
	i = 0;
	ft_printf("ID\t|\tNAME\t|\tDATA\n\n");
	while (i < e->nb_players)
	{
		ft_printf("%d\t| %s\t| ", e->proc[i].id, e->proc[i].name);
		off = 0;
		while (off < e->proc[i].file_size)
		{
			ft_printf("%02x", ((char *)(e->proc[i].file))[off]);
			off++;
			if (off % 4 == 0)
				ft_printf(" ");
		}
		ft_printf("\n");
		i++;
	}
}

static void		debug_map(unsigned char *arena, size_t size)
{
	size_t		i;

	i = 0;
	ft_printf("ARENA\n");
	while (i < size)
	{
		ft_printf("%02X", arena[i]);
		i++;
		if (i % 32 == 0)
			ft_printf("\n");
		else
			ft_printf(" ");
	}
}

int				main(int ac, char **av)
{
	t_env	e;

	ft_memset(&e, 0, sizeof(e));
	e.progname = ft_strrchr(av[0], '/');
	e.progname = (e.progname) ? e.progname + 1 : av[0];
	if (ac < 2 || get_args(av, &e) || get_champions(&e) || get_arena(&e))
		return (usage(av[0]));
	debug_champ(&e);
	debug_map(e.arena, MEM_SIZE);
	free_env(&e);
	return (42);
}
