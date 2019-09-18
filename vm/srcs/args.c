/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 00:25:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/18 03:03:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

static int		get_dump(char **av, int i, t_env *e)
{
	int			j;

	j = 0;
	while (av[i][j] && ft_isdigit(av[i][j]))
		j++;
	if (!av[i][j])
	{
		e->nb_cycle = ft_atoi(av[i]);
		if (e->nb_cycle > 0)
			return (1);
		return (ERR_NEGATIVE);
	}
	return (ERR_DIGIT);
}

static int		check_numbers(char **av, int i, t_env *e)
{
	int			j;

	j = 0;
	while (av[i][j] && ft_isdigit(av[i][j]))
		j++;
	if (!av[i][j])
	{
		e->proc[e->nb_players].id = ft_atoi(av[i]);
		if (e->proc[e->nb_players].id > 0)
			return (0);
		return (ERR_NEGATIVE);
	}
	return (ERR_DIGIT);
}

static int		get_id(t_env *e, char *av)
{
	int		i;

	i = 0;
	while (i < e->nb_players)
	{
		if (e->proc[i].id == e->proc[e->nb_players].id)
			return (ERR_NUMBER);
		i++;
	}
	return (0);
}

int			store_id(t_env *e, char *av)
{
	if (e->nb_players >= MAX_PLAYERS)
		return (ERR_MAX_CHAMP);
	if (e->proc[e->nb_players].id == 0)
	{
		/* Aucun numero de joueur n'a été défini, c'est a la VM de le faire */
		e->proc[e->nb_players].id = 1;
		int p = 0;
		while (p < e->nb_players)
		{
			if (e->proc[e->nb_players].id == e->proc[p].id)
			{
				e->proc[e->nb_players].id++;
				p = 0;
			}
			else
				p++;
		}
		e->proc[p].name = av;
	}
	else if (get_id(e, av))
		return (ERR_NUMBER);
	e->nb_players++;
	return (0);
}

static int		get_args_error(int errnb, char *av, t_env *e)
{
	static char	*error[] = {
		NULL,
		"value must contains only numbers",
		"value must be strictly positive",
		"unknown parameter",
		"invalid filename",
		"too many champions received",
		"number already taken",
	};

	ft_dprintf(2, "%s: %s '%s'\n\n", e->progname, error[errnb], av);
	return (1);
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
		if (ft_strequ(av[i], "-dump"))
			err = get_dump(av, ++i, e);
		else if (ft_strequ(av[i], "-n"))
			err = check_numbers(av, ++i, e);
		else if ((tmp = ft_strrchr(av[i], '.')) && ft_strequ(tmp, ".cor"))
			err = store_id(e, av[i]);
		else
			err = (av[i][0] == '-') ? ERR_PARAM : ERR_FILENAME;
		if (err)
			return (get_args_error(err, av[i], e));
		i++;
	}
	return (0);
}
