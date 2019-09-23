/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:54:39 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 03:26:38 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_HEXDUMP_H
# define CW_HEXDUMP_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <ncurses.h>
# include <curses.h>
# include <pthread.h>
# include <unistd.h>

# define ERR_OPEN	-1
# define ERR_MALLOC 5

# define FLAG_N		(1 << 0)

# define NAME		1
# define COMMENT	2
# define PADDING	4

# define COR_EXT	".cor"

# define LIVE		{1, "live"}//, &w_live}
# define LD			{2, "ld"}//, &w_ld}
# define ST			{3, "st"}//, &w_st}
# define ADD		{4, "add"}//, &w_add}
# define SUB		{5, "sub"}//, &w_sub}
# define AND		{6, "and"}//, &w_and}
# define OR			{7, "or"}//, &w_or}
# define XOR		{8, "xor"}//, &w_xor}
# define ZJMP		{9, "zjmp"}//, &w_zjmp}
# define LDI		{10, "ldi"}//, &w_ldi}
# define STI		{11, "sti"}//, &w_sti}
# define FORK		{12, "fork"}//, &w_fork}
# define LLD		{13, "lld"}//, &w_lld}
# define LLDI		{14, "lldi"}//, &w_lldi}
# define LFORK		{15, "lfork"}//, &w_lfork}
# define AFF		{16, "aff"}//, &w_aff}

# define DIRECT		1
# define INDIRECT	2
# define REGISTER	3

typedef struct		s_data
{
	short			t_bin;
	int				pc;
	int				print_cursor;
	int				fd;
	int				flag;
	int				type[3];
	int				size;
	WINDOW			*main_win;
	char			*name;
	char			*comment;
	char			*file_name;
//	void			(*func)(struct s_data *data);
}					t_data;

typedef struct		s_opc
{
	int				code;
	char			*opcode;
//	void			(*func)(t_data *data);
}					t_opc;

typedef struct		s_thread
{
	WINDOW			*main_win;
	int				stop;
}					t_thread;

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

int			init_screen(t_data *data);
int			wait_or_enter(t_data *data, int sleeping);

#endif 
