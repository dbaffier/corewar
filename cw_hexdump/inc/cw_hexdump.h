/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:54:39 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/21 01:21:50 by mmonier          ###   ########.fr       */
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

# define NAME		1
# define COMMENT	2

# define COR_EXT	".cor"

# define LIVE		{1, "live"}
# define LD			{2, "ld"}
# define ST			{3, "st"}
# define ADD		{4, "add"}
# define SUB		{5, "sub"}
# define AND		{6, "and"}
# define OR			{7, "or"}
# define XOR		{8, "xor"}
# define ZJMP		{9, "zjmp"}
# define LDI		{10, "ldi"}
# define STI		{11, "sti"}
# define FORK		{12, "fork"}
# define LLD		{13, "lld"}
# define LLDI		{14, "lldi"}
# define LFORK		{15, "lfork"}
# define AFF		{16, "aff"}

# define DIRECT		1
# define INDIRECT	2
# define REGISTER	3

typedef struct		s_data
{
	int				cursor;
	int				fd;
	int				type[3];
	short			t_bin;
	char			*name;
	char			*comment;
	int				size;
}					t_data;

typedef struct		s_opc
{
	int				code;
	char			*opcode;
}					t_opc;

//////////// main hexdump
int			cw_hexdump(t_data *data, char *file);
int			way_to_corewar(t_data *data);

//////////// generate .cor
int			create_corfile(char *file);

//////////// flush memory
void		dump(char *file, void * addr, int len);

//////////// write func
void		write_type(t_data *data);
void		write_opc(t_data *data, char *opc);
void		write_param(t_data *data, char *param, int size);

/*
** Header functions
*/

void		write_header(t_data *data, int type);
////////// write magic number
void		write_magic(t_data *data);
////////// binary conversion
short		binary(char c);

#endif 
