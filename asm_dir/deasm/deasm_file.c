/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:23:29 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/30 04:06:54 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"
#include <stdio.h>

static void		dswrite_instructions(t_info *inf, char buff)
{
	unsigned int cast;

	cast = (unsigned int)buff;
	if (inf->cursor == 2191)
	{
		write(inf->ds_fd, "\n\n", 2);
		inf->decode = OPC;
	}
	else if (inf->decode == OPC)
	{
		dswrite_opc(inf, buff);
		if (buff != 1 || buff != 9 || buff != 12 || buff != 15)
			inf->decode = E_BYTE;
		else
			inf->decode = PARAM; 
	}
	else if (inf->decode == E_BYTE)
	{
		decode_types(inf, (cast>> 2));
		inf->decode = PARAM; 
	}
	else if (inf->decode == PARAM)
		dswrite_param(inf, buff);
	else 
		inf->decode = END;
}

static void		dswrite(t_info *inf, char buff)
{
	if (inf->cursor == 4)
		write(inf->ds_fd, ".name : \"", 9);
	if (inf->cursor == 136)
		write(inf->ds_fd, "\"\ncomment : \"", 13);
	write(inf->ds_fd, &buff, 1);
}

int				deasm_file(t_info *inf)
{
	char	buff;
	int		i;

	if ((inf->ds_fd = open(inf->ds_name, O_CREAT | O_TRUNC | O_RDWR, 0700)) == -1)
		return (DS_ERR_OPEN);
	lseek(inf->fd, 4, SEEK_SET);
	inf->cursor = 4;
	i = 0;
	while (read(inf->fd, &buff, 1) > 0)
	{
		if (inf->cursor < 2191)
			dswrite(inf, buff);
		if (inf->cursor >= 2191)
		{
			if (inf->decode == OPC)
				i = 0;
			if (inf->decode == PARAM)
			{
				if (inf->type[i] == TYPE_DIR)
				{
					if (inf->dir_size == 4)
						inf->cursor = inf->cursor + 3;
					else
						inf->cursor = inf->cursor + 1;
					lseek(inf->fd, inf->cursor, SEEK_SET);
				}
				if (inf->type[i] == TYPE_IND)
				{
					inf->cursor = inf->cursor + 1;
					lseek(inf->fd, inf->cursor + 1, SEEK_SET);
				}
				dswrite_instructions(inf, buff);
				i++;
			}
		}
		inf->cursor = inf->cursor + 1;
	}
	return (0);
}
