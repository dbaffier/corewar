/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:51:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/06 16:23:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static int		get_number(char *av, int *value)
{
	int			i;

	i = 0;
	if (!av)
		return (ERR_DIGIT);
	while (av[i] && ft_isspace(av[i]))
		i++;
	if (av[i] == '-')
		i++;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (!av[i])
	{
		if ((*value = ft_atoi(av)) == 0)
			return (ERR_ZERO);
		return (IS_OK);
	}
	return (ERR_DIGIT);
}

static int		get_option(int *i, char **av, t_env *e)
{
	if (ft_strequ(av[*i], "-dump"))
		return (get_number(av[++(*i)], (int *)&e->dump_cycle));
	if (ft_strequ(av[*i], "-n"))
		return (get_number(av[++(*i)], &e->id));
	if (ft_strequ(av[*i], "-h"))
		return (ERR_HELP);
	if (ft_strequ(av[*i], "-v"))
		e->ncu.active = TRUE;
	return (IS_OK);
}

int				get_args(char **av, t_env *e)
{
	int		i;
	char	*tmp;
	int		err;

	i = 1;
	err = 0;
	while (av[i])
	{
		if (av[i][0] == '-')
			err = get_option(&i, av, e);
		else if ((tmp = ft_strrchr(av[i], '.')) && ft_strequ(tmp, ".cor"))
			err = get_player(e, av[i]);
		else
			err = (av[i][0] == '-') ? ERR_PARAM : ERR_FILENAME;
		if (err)
			return (corewar_errors(err, av[i], e));
		i++;
	}
	if (!e->nb_players)
		return (corewar_errors(ERR_NO_CHAMP, NULL, e));
	return (0);
}
