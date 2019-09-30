/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dswrite_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 01:14:48 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/30 03:57:27 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"
#include <stdio.h>

void		dswrite_opc(t_info *inf, char buff)
{
	static char		*tab[17] = {NULL, "live", "ld", "st", "add", "sub", "and", "or",
								"xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi",
								"lfork", "aff"};
	unsigned int	i;
	
	i = (unsigned int)buff;
	write(inf->ds_fd, tab[i], ft_strlen(tab[i]));
	if ((i >= 1 && i <= 8) || i == 13 || i == 16)
		inf->dir_size = 4;
	else
		inf->dir_size = 2;
}

static void	check_type(t_info *inf, int j)
{
	if (inf->curr[0] == 0 && inf->curr[1] == 1)
	{
		inf->type[j] = TYPE_REG;
		inf->n_param = inf->n_param + 1;
	}
	else if (inf->curr[0] == 1 && inf->curr[1] == 0)
	{
		inf->type[j] = TYPE_DIR;
		inf->n_param = inf->n_param + 1;
	}
	else if (inf->curr[0] == 1 && inf->curr[1] == 0)
	{
		inf->type[j] = TYPE_IND;
		inf->n_param = inf->n_param + 1;
	}
}

void		decode_types(t_info *inf, unsigned int buff)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (buff > 0)
	{
		if (i == 2)
		{
			check_type(inf, j);
			inf->curr[0] = 0;
			inf->curr[1] = 0;
			i = 0;
			j++;
		}
		inf->curr[i] = 1 & buff;
		i++;
		buff >>= 1;
	}
}

void		dswrite_param(t_info *inf, char buff)
{
	static int i = -1;

	i++;
	if (inf->type[i] == TYPE_REG)
	{
		write(inf->ds_fd, "r", 1);
		write(inf->ds_fd, &buff, 1);
	}
	if (inf->type[i] == TYPE_DIR)
	{
		write(inf->ds_fd, "%", 1);
		write(inf->ds_fd, &buff, 1);
	}
	if (inf->type[i] == TYPE_IND)
		write(inf->ds_fd, &buff, 1);
	if (i < inf->n_param)
		write(inf->ds_fd, ", ", 2);
	else
	{
		write(inf->ds_fd, "\n", 1);
		inf->decode = OPC;
		i = -1;
	}	
}
