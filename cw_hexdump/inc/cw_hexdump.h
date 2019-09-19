/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:54:39 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/19 22:19:33 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_HEXDUMP_H
# define CW_HEXDUMP_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define ERR_OPEN	-1
# define ERR_MALLOC 5

# define COR_EXT	".cor"

# define LIVE	{"01", "live"}
# define LD		{"02", "ld"}
# define ST		{"03", "st"}
# define ADD	{"04", "add"}
# define SUB	{"05", "sub"}
# define AND	{"06", "and"}
# define OR		{"07", "or"}
# define XOR	{"08", "xor"}
# define ZJMP	{"09", "zjmp"}
# define LDI	{"0a", "ldi"}
# define STI	{"0b", "sti"}
# define FORK	{"0c", "fork"}
# define LLD	{"0d", "lld"}
# define LLDI	{"0e", "lldi"}
# define LFORK	{"0f", "lfork"}
# define AFF	{"10", "aff"}

typedef struct		s_data
{
	int				cursor;
	int				fd;
	int				prec_type;
}					t_data;

typedef struct		s_opc
{
	int				code;
	char			*opcode;
}					t_opc;

int			cw_hexdump(char *file);
int			create_corfile(char *file);
void		dump(char *file, void * addr, int len);

#endif 
