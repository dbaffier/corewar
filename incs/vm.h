/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:03:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/17 19:16:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"

typedef struct		s_process
{
	char		position;
	char		*name;
	char		reg[REG_NUMBER][REG_SIZE];
	char		pc[REG_SIZE];
	char		carry;
}					t_process;

typedef struct		s_env
{
	size_t		nb_cycle;
	t_process	proc[MAX_PLAYERS];
}					t_env;

#endif
