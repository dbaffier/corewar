/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:29:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/19 02:23:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int				get_arena(t_env *e)
{
	int			i;

	i = 0;
	if ((e->arena = ft_memalloc(MEM_SIZE)) == NULL)
		return (ERR_MALLOC);
	while (i < e->nb_players)
	{
		
		i++;
	}
	return (IS_OK);
}
