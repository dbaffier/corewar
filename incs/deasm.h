/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 23:19:59 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/30 03:49:14 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEASM_H
# define DEASM_H

# include "libft.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <unistd.h>

# define DS_ERR_OPEN		1
# define DS_ERR_MALLOC		2
# define DS_ERR_EXTENSION	3

# define DOT_COR			".cor"
# define DOT_DS				".d.s"

# define END				0
# define OPC				1
# define E_BYTE				2
# define PARAM				3

# define TYPE_REG			1
# define TYPE_DIR			2
# define TYPE_IND			3

typedef struct		s_info
{
	int				fd;
	int				ds_fd;
	int				cursor;
	int				decode;
	int				n_param;
	int				dir_size;
	int				type[3];
	int				curr[2];
	char			*ds_name;
}					t_info;			

int			deasm_file(t_info *inf);

/*
** dswrite_instructions.c
*/
void		dswrite_opc(t_info *inf, char buff);
void		dswrite_param(t_info *inf, char buff);
void		decode_types(t_info *inf, unsigned int buff);

#endif
