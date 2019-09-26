/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:54:39 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 00:45:53 by mmonier          ###   ########.fr       */
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
# include <sys/types.h>
# include <signal.h>

# define ERR_OPEN	-1
# define ERR_MALLOC 5
# define ERR_FLAG	6

# define FLAG_N		(1 << 0)
# define FLAG_O		(1 << 1)

# define DASH_N		{FLAG_N, 'n'}
# define DASH_O		{FLAG_O, 'o'}

# define NAME		1
# define COMMENT	2
# define PADDING	4

# define COR_EXT	".cor"
# define MSG		"With this visu you will be able to see a bit more about how corewar works"
# define ZERO_LINE	"00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00"

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
	int				pos;
	int				pc;
	int				x;
	int				y;
	int				fd;
	int				flag;
	int				type[3];
	int				size;
	int				i;
	int				zero;
	int				check;
	WINDOW			*main_win;
	char			*name;
	char			*comment;
	char			*file_name;
	unsigned char	*buffer;
//	void			(*func)(struct s_data *data);
}					t_data;

typedef struct		s_flags
{
	int				msk;
	char			opt;
}					t_flags;

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

int			parse_flag(t_data *data, char **av);
void		print_usage(int error);
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
short		binary(char dec);

int			init_screen(t_data *data);
int			wait_or_enter(t_data *data, int sleeping);
void		print_hex(t_data *data);
void		print_buff(t_data *data);
int			fill_buffer(t_data *data, unsigned char buff);
int			len_hex(unsigned char bin);
void		nprint_nb(t_data *data, int base, unsigned char n, char letter);
void		print_file_name(t_data *data);
void		print_compilation(t_data *data);
void		print_dot(t_data *data);
void		print_end(t_data *data);
void		print_menu(t_data *data);
void		starting_color(t_data *data);
void		reset_colors(t_data *data);
void		print_legend(t_data *data, int x, int y);
void		print_offset(t_data *data);

#endif 
