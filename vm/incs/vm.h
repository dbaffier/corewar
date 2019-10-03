/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:16:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/03 18:50:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <unistd.h>
# include <stdlib.h>
# include "op.h"
# include "vm_ncurse.h"

# if REG_SIZE == 1
#  define REG_CAST uint8_t
# elif REG_SIZE == 2
#  define REG_CAST unsigned short
# elif REG_SIZE == 4
#  define REG_CAST unsigned int
# else
#  define REG_CAST unsigned long
# endif

/*
** Corewar error codes
*/

enum
{
	IS_OK,
	ERR_HELP,
	ERR_DIGIT,
	ERR_NEGATIVE,
	ERR_PARAM,
	ERR_FILENAME,
	ERR_MAX_CHAMP,
	ERR_NUMBER,
	ERR_NO_CHAMP,
	ERR_OPEN,
	ERR_LSEEK,
	ERR_MALLOC,
	ERR_READ,
	ERR_SIZE_LOW,
	ERR_MAGIC,
	ERR_SIZE_DIFF,
	ERR_SIZE_HIGH,
	ERR_NCURSE_MAINWIN,
	ERR_NCURSE_ARENABOX,
	ERR_NCURSE_ARENAWIN,
	ERR_NCURSE_INFOBOX,
	ERR_NCURSE_CHAMPWIN,
	ERR_NCURSE_VMWIN,
	ERR_NCURSE_INFOWIN,
};

typedef struct			s_live
{
	int					last_id;
	char				name[PROG_NAME_LENGTH + 1];
}						t_live;

typedef struct			s_process
{
	int					pos;
	int					id;
	char				*file_name;
	off_t				file_size;
	void				*file;
	int					data_size;
	char				reg[REG_NUMBER][REG_SIZE];
	char				pc[REG_SIZE];
	char				carry;
	size_t				instruction_wait;
	uint8_t		instruction;
	size_t				is_alive;
	short				color[2];
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct			s_env
{
	char				*progname;
	t_ncurse			ncu;
	int					dump_cycle;
	int					id;
	int					nb_players;
	t_process			*proc;
	void				*arena;
	short				*colors;
	int					pause;
	int					speed;
	int					cycle_to_die;
	int					checks;
	t_live				live;
	int					term_too_small;
}						t_env;

struct s_env			g_env;

typedef struct			s_param
{
	int					value;
	char				size;
}						t_param;

/*
** Signals Handlers
*/
void					corewar_end(int i);
void					ncurses_resizewindow(int sig);

/*
** Errors && Free Functions
*/
int						corewar_errors(int errnb, char *arg, t_env *e);
void					free_env(t_env *e);

/*
** Get arguments Functions
*/
int						get_args(char **av, t_env *e);
int						get_player(t_env *e, char *av);
int						get_arena(t_env *e);
int						get_colors(t_env *e);
t_process				*remove_player(t_process *proc, t_process **head);

/*
** Ncurses Functions
*/
int						ncurses_init(t_env *e);
void					ncurses_end(t_env *e);
int						ncurses_termtoosmall(t_env *e);
int						create_arenabox(t_env *e);
int						create_infobox(t_env *e);
void					ncurses_aff_all(t_env *e);
void					update_aff_vminfo(t_env *e, size_t cycle);
void					update_aff_vmstatus(t_env *e);
void					update_aff_champion_dead(t_env *e, t_process *proc);
void					update_aff_arena(char *arena, size_t size,
						short color, t_env *e);

/*
** Game Functions
*/
void					launch_game(t_env *e);
int						play_game(size_t nb_cycles, t_env *e);
void					dump_map(uint8_t *arena, size_t size);
void					move_process_pc(t_process *proc, int len, t_env *e);
REG_CAST				calc_mod(int len, size_t size);
void					arena_copy(void *arena, REG_CAST pc, REG_CAST *value,
						size_t size);
REG_CAST				arena_get(void *arena, REG_CAST pc, size_t size);
void					color_copy(short *colors, REG_CAST pc, short color,
						size_t size);
uint16_t				byteswap_16(uint16_t x);
uint32_t				byteswap_32(uint32_t x);

/*
** Instructions Functions
*/
void					op_live(t_process *proc, t_env *e);
void					op_ld(t_process *proc, t_env *e);
void					op_st(t_process *proc, t_env *e);
void					op_add(t_process *proc, t_env *e);
void					op_sub(t_process *proc, t_env *e);
void					op_and(t_process *proc, t_env *e);
void					op_or(t_process *proc, t_env *e);
void					op_xor(t_process *proc, t_env *e);
void					op_zjmp(t_process *proc, t_env *e);
void					op_ldi(t_process *proc, t_env *e);
void					op_sti(t_process *proc, t_env *e);
void					op_fork(t_process *proc, t_env *e);
void					op_lld(t_process *proc, t_env *e);
void					op_lldi(t_process *proc, t_env *e);
void					op_lfork(t_process *proc, t_env *e);
void					op_aff(t_process *proc, t_env *e);

void					handle_st(t_param *params, t_process *proc, t_env *e);
void					handle_sti(t_param *params, t_process *proc, t_env *e);

void					get_params_len(t_param *params, int nbparam,
						char types, char opcode);
void					get_params_data(t_param *params, int nbparam,
						uint8_t *arena, REG_CAST pc);
t_process				*new_proc(t_process *proc, int value, int flag,
						t_env *e);
void					get_types(char types, t_param *params_type);
int						get_value(uint8_t *data, int index,
						int size);
int						full_len_size(unsigned short reg_nb,
						t_param *params);
void					print_live(t_env *e, t_param *params, t_process *tail);

#endif
