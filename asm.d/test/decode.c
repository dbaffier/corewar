/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:50:26 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/04 23:22:01 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static int checktype(t_print *print, int *tmp)
{
	if (tmp[0] == 0 && tmp[1] == 0)
		return (E_NONE);
	print->ninstruc += 1;
	if (tmp[0] == 1 && tmp[1] == 0)
		return (E_REG);
	if (tmp[0] == 0 && tmp[1] == 1)
		return (E_DIR);
	return (E_IND);
}

void	decode(t_print *print, unsigned int buff)
{
	int tmp[2];
	int	j;
	int	i;
	
	j = 0;
	i = 0;
	buff >>= 2;
	while (j < 3)
	{
		if (i > 1)
		{
			print->param[j] = checktype(print,tmp);
			j++;
			i = 0;
		}
		tmp[i] = 1 & buff;
		i++;
		buff >>= 1;
	}
	print->idx = 0;
}
