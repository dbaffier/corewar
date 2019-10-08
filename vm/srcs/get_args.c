/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:51:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/08 05:33:15 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static int	get_number(char *av, int *value, int zero)
{
	int		i;

	i = 0;
	if (!av)
		return (ERR_MISSING_ARG);
	while (av[i] && ft_isspace(av[i]))
		i++;
	if (av[i] == '-')
		i++;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (!av[i])
	{
		if ((*value = ft_atoi(av)) == 0 && !zero)
			return (ERR_ZERO);
		return (IS_OK);
	}
	return (ERR_DIGIT);
}

static int	get_option(int *i, char **av, t_env *e)
{
	if (ft_strequ(av[*i], "-dump"))
		return (get_number(av[++(*i)], &e->dump_cycle, 1));
	if (ft_strequ(av[*i], "-n"))
		return (get_number(av[++(*i)], &e->id, 0));
	if (ft_strequ(av[*i], "-h"))
		return (ERR_HELP);
	if (ft_strequ(av[*i], "-v"))
	{
		e->ncu.active = TRUE;
		return (IS_OK);
	}
	return (ERR_UNKNOWN_ARG);
}

int			get_args(int *ac, char **av, t_env *e)
{
	char	*tmp;
	int		err;
	int		i;

	err = (*ac > 1) ? IS_OK : ERR_MISSING_ARG;
	i = 1;
	e->dump_cycle = -1;
	e->ncu.active = FALSE;
	while (av[i] && err == IS_OK)
	{
		if (av[i][0] == '-')
			err = get_option(&i, av, e);
		else if ((tmp = ft_strrchr(av[i], '.')) && ft_strequ(tmp, ".cor"))
			err = get_player(e, av[i]);
		else
			err = ERR_FILENAME;
		if (err == IS_OK)
			i++;
	}
	if (err == IS_OK && !e->nb_players)
		err = ERR_NO_CHAMP;
	*ac = i;
	return (err);
}
