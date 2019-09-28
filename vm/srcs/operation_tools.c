/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:05:26 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/27 00:34:50 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

t_process	*new_proc(t_process *proc, int value, int flag)
{
	t_process *new;

	new = ft_memalloc(sizeof(t_process));
	ft_memcpy(new, proc, sizeof(t_process));
	if (!flag)
		*(REG_CAST *)new->pc = (*(REG_CAST *)proc->pc + value) % IDX_MOD;
	else
		*(REG_CAST *)new->pc = (*(REG_CAST *)proc->pc + value);
	new->prev = proc;
	if ((new->next = proc->next) != NULL)
		new->next->prev = new;
	return (new);
}

void	get_types(char types, t_param *params_type)
{
	unsigned char	param_len;
	int				i;

	i = 0;
	while (i < 3)
	{	
		param_len = types;
		param_len = param_len >> 6;
		params_type[i].size = param_len;
		types = types << 2;
		i++;
	}
}

void	get_params_len(t_param *params, int nbparam, char types, char opcode)
{
	int		i;

	get_types(types, params);
	i = 0;
	while (i < nbparam)
	{
		if (params[i].size == 1)
			params[i].size = 1;
		else if (params[i].size == 2)
		{
			if (opcode == 9 || opcode == 10 || opcode == 11 || opcode == 12 ||
					opcode == 14 || opcode == 15)
				params[i].size = 2;
			else
				params[i].size = 4;
		}
		else if (params[i].size == 3)
			params[i].size = 2;
		else
			params[i].size = 0;
		i++;
	}
}

int		get_value(unsigned char *data, int index, int size)
{
	int		i;
	char	tab[size];

	i = 0;
	(void)index;
	while (i < size)
	{
		tab[i] = data[1 + i];
		i++;
	}
	tab[i] = '\0';
	return (ft_atoi_base(tab, 16));
}

void	get_params_data(t_param *params, int nbparam, unsigned char *data, int pc)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	(void)pc;
	while (i < nbparam)
	{
		if (*data == 9 || *data == 1 || *data == 12 || *data == 15)
			params[i].value = get_value(data, 1, params[i].size);
		else
			params[i].value = get_value(data, size + 2, params[i].size);
		size += params[i].size;
		ft_printf("value [%d] = [%d]\n", i + 1, params[i].value);
		i++;
	}
}
