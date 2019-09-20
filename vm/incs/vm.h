/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:03:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/21 01:23:59 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include <unistd.h>

# if REG_SIZE == 1
#  define REG_CAST char
# elif REG_SIZE == 2
#  define REG_CAST short
# elif REG_SIZE == 4
#  define REG_CAST int
#endif

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

typedef struct		s_process
{
	int				id;
	char			*name;
	off_t			file_size;
	void			*file;
	int				data_size;
	char			reg[REG_NUMBER][REG_SIZE];
	char			pc[REG_SIZE];
	char			carry;
	int				cycle_left;
	int				is_alive;
	int				is_dead;
}					t_process;

typedef struct		s_param

	char			param_data[4];
	int				param_size;
	char			param_type;ss
}					t_param;

typedef struct		s_env
{
	char			*progname;
	int				nb_cycle;
	int				nb_players;
	t_process		proc[MAX_PLAYERS];
	void			*arena;
	size_t			nb_cycles;
}					t_env;

void				free_env(t_env *e);

int					corewar_errors(int errnb, char *arg, t_env *e);

int					get_args(char **av, t_env *e);
int					get_champions(t_env *e);
int					get_arena(t_env *e);

void				launch_game(t_env *e);

#endif
