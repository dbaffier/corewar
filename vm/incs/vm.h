/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:16:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/25 13:25:14 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <unistd.h>
# include "op.h"

# if REG_SIZE == 1
#  define REG_CAST char
# elif REG_SIZE == 2
#  define REG_CAST short
# elif REG_SIZE == 4
#  define REG_CAST int
# else
#  define REG_CAST long
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
	ERR_FORK,
	ERR_NCU_INIT,
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
};

typedef struct			s_live
{
	int					last_id;
	char				last_name[PROG_NAME_LENGTH + 1];
	size_t				total;
}						t_live;

typedef struct			s_process
{
	int					id;
	char				*file_name;
	off_t				file_size;
	void				*file;
	int					data_size;
	char				reg[REG_NUMBER][REG_SIZE];
	char				pc[REG_SIZE];
	char				carry;
	size_t				instruction_wait;
	int					instruction;
	int					is_alive; /* must be 0 or 1 */
	t_live				*live;
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct			s_param
{
	int					value;
	char				size;
}						t_param;

typedef struct			s_env
{
	char				*progname;
	pid_t				pid;
	int					dump_cycle;
	int					id;
	int					nb_players;
	t_process			*proc;
	void				*arena;
	int					cycle_to_die;
	int					checks;
	t_live				live;
}						t_env;

int						corewar_errors(int errnb, char *arg, t_env *e);
void					free_env(t_env *e);

int						get_args(char **av, t_env *e);
int						get_player(t_env *e, char *av);
int						get_arena(t_env *e);
t_process				*remove_player(t_process *proc, t_process **head);

int						ncurse_view(t_env *e);
void					ncurses_end(void);

void					launch_game(t_env *e);
void					dump_map(unsigned char *arena, size_t size);

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
void					op_ldi(t_process *proc, t_env *e);
void					op_lfork(t_process *proc, t_env *e);
void					op_aff(t_process *proc, t_env *e);

void					get_params_len(t_param *params, int nbparam, \
		char types, char opcode);
void					get_params_data(t_param *params, int nbparam, \
		unsigned char *data, int pc);
t_process				*new_proc(t_process *proc, int value);
#endif
