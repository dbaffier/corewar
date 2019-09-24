/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:03:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/23 03:20:23 by bmellon          ###   ########.fr       */
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
};

typedef struct			s_live
{
	int					id;
	struct s_live		*next;
}						t_live;

typedef struct			s_process
{
	int					id;
	char				*name;
	off_t				file_size;
	void				*file;
	int					data_size;
	char				reg[REG_NUMBER][REG_SIZE];
	char				pc[REG_SIZE];
	char				carry;
	int					cycle_left;
	int					is_alive;
	int					is_dead;
	t_live				**live;
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
	int					dump_cycle;
	int					id;
	int					nb_players;
	t_process			*proc;
	void				*arena;
	size_t				nb_cycles;
	t_live				*live;
}						t_env;

void					free_env(t_env *e);

int						corewar_errors(int errnb, char *arg, t_env *e);

int						get_args(char **av, t_env *e);
int						get_player(t_env *e, char *av);
int						get_arena(t_env *e);

void					launch_game(t_env *e);

void					op_live(t_op *op, t_env *e, int i);
void					op_ld(t_op *op, t_env *e, int i);
void					op_st(t_op *op, t_env *e, int i);
void					op_add(t_op *op, t_env *e, int i);
void					op_sub(t_op *op, t_env *e, int i);
void					op_and(t_op *op, t_env *e, int i);
void					op_or(t_op *op, t_env *e, int i);
void					op_xor(t_op *op, t_env *e, int i);
void					op_zjmp(t_op *op, t_env *e, int i);
void					op_ldi(t_op *op, t_env *e, int i);
void					op_sti(t_op *op, t_env *e, int i);
void					op_fork(t_op *op, t_env *e, int i);
void					op_lld(t_op *op, t_env *e, int i);
void					op_ldi(t_op *op, t_env *e, int i);
void					op_lfork(t_op *op, t_env *e, int i);
void					op_aff(t_op *op, t_env *e, int i);

void					get_params_len(t_param *params, int nbparam, \
		char types, char opcode);
void					get_params_data(t_param *params, int nbparam, \
		char *data, int pc);
#endif
