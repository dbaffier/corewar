/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:03:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/18 02:49:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"

enum
{
	ERR_DIGIT = 1,
	ERR_NEGATIVE,
	ERR_PARAM,
	ERR_FILENAME,
	ERR_MAX_CHAMP,
	ERR_NUMBER,
};

typedef struct		s_process
{
	int				id;
	char			*name;
	char			reg[REG_NUMBER][REG_SIZE];
	char			pc[REG_SIZE];
	char			carry;
}					t_process;

typedef struct		s_env
{
	char			*progname;
	int				nb_cycle;
	int				nb_players;
	t_process		proc[MAX_PLAYERS];
}					t_env;

int					get_args(char **av, t_env *e);

#endif
