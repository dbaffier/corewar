/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 00:25:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/18 18:40:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

static int		get_number(char *av, int *value)
{
	int			i;

	i = 0;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (!av[i])
	{
		*value = ft_atoi(av);
		if (*value > 0)
			return (IS_OK);
		return (ERR_NEGATIVE);
	}
	return (ERR_DIGIT);
}

static int		get_id(t_env *e, int *i)
{
	*i = 0;
	while (*i < e->nb_players)
	{
		if (e->proc[*i].id == e->proc[e->nb_players].id)
			return (ERR_NUMBER);
		(*i)++;
	}
	return (IS_OK);
}

static int		store_id(t_env *e, char *av)
{
	int			i;

	i = 0;
	if (e->nb_players >= MAX_PLAYERS)
		return (ERR_MAX_CHAMP);
	if (e->proc[e->nb_players].id == 0)
	{
		e->proc[e->nb_players].id = 1;
		while (i < e->nb_players)
		{
			if (e->proc[e->nb_players].id == e->proc[i].id)
			{
				e->proc[e->nb_players].id++;
				i = 0;
			}
			else
				i++;
		}
	}
	else if (get_id(e, &i))
		return (ERR_NUMBER);
	e->proc[i].name = av;
	e->nb_players++;
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
		if (ft_strequ(av[i], "-dump"))
			err = get_number(av[++i], &e->nb_cycle);
		else if (ft_strequ(av[i], "-n"))
			err = get_number(av[++i], &e->proc[e->nb_players].id);
		else if ((tmp = ft_strrchr(av[i], '.')) && ft_strequ(tmp, ".cor"))
			err = store_id(e, av[i]);
		else
			err = (av[i][0] == '-') ? ERR_PARAM : ERR_FILENAME;
		if (err)
			return (corewar_errors(err, av[i], e));
		i++;
	}
	if (!e->nb_players)
		return (corewar_errors(ERR_NO_CHAMP, NULL, e));
	return (IS_OK);
}
