/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:05:26 by bmellon           #+#    #+#             */
/*   Updated: 2019/10/06 16:14:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

t_process	*new_proc(t_process *proc, int value, int flag, t_env *e)
{
	t_process *new;

	new = ft_memalloc(sizeof(*new));
	ft_memcpy(new, proc, sizeof(*new));
	new->free_file[proc->pos]++;
	new->instruction_wait += 1;
	new->instruction = 0;
	if (!flag)
		move_process_pc(new, value % IDX_MOD, e);
	else
		move_process_pc(new, value, e);
	new->prev = proc;
	if ((new->next = proc->next) != NULL)
		new->next->prev = new;
	return (new);
}

void		get_params_len(t_param *params, t_op *op, uint8_t types)
{
	int		i;

	i = 0;
	if (op->reg_nb == 1)
	{
		params[0].type = op->types[0];
		params[0].size = (op->opcode == 1) ? 4 : 2;
		return ;
	}
	while (i < op->reg_nb)
	{
		params[i].type = types >> 6;
		if (params[i].type == REG_CODE)
			params[i].size = 1;
		else if (params[i].type == DIR_CODE)
			params[i].size = (op->direct_size) ? 2 : 4;
		else if (params[i].type == IND_CODE)
			params[i].size = 2;
		types = types << 2;
		i++;
	}
}

static int	get_value(uint8_t *data, int index, int size)
{
	int		i;
	int		j;
	char	tab[REG_SIZE];

	ft_bzero(tab, REG_SIZE);
	i = 0;
	j = REG_SIZE - 1;
	if (size > REG_SIZE)
		return (0);
	while (size--)
	{
		tab[size] = data[(index + i) % MEM_SIZE];
		i++;
	}
	if (size == 2)
		return (*(short *)tab);
	return (*(int *)tab);
}

void		get_params_data(t_param *params, t_op *op, uint8_t *arena,
REG_CAST pc)
{
	uint8_t	*data;
	int		i;
	int		size;

	data = arena + pc;
	i = 0;
	size = 0;
	while (i < op->reg_nb)
	{
		if (op->reg_nb == 1)
			params[i].value = get_value(arena, pc + 1, params[i].size);
		else
			params[i].value = get_value(arena, pc + size + 2, params[i].size);
		size += params[i].size;
		i++;
	}
}
