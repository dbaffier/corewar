/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:05:26 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/23 03:20:21 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	get_types(char types, t_param *params_type)
{
	char	param_len;
	int		i;
	
	i = 0;
	while (i < 3)
	{	
		param_len = types;
		param_len = param_len >> 6;
		params_type[i].param_size = param_len;
		types = types << 2;
		i++;
	}
}


void	get_params_len(t_param *params, int nbparam, char types, char opcode)
{
	int		i;

	get_types(types, params);
	i = 0;
	while (nbparam > 0)
	{
		if (params[i].param_size == 1)
			params[i].param_size = 1;
		else if (params[i].param_size == 2)
		{
			if (opcode == 9 || opcode == 10 || opcode == 11 || opcode == 12 ||
					opcode == 14 || opcode == 15)
				params[i].param_size = 2;
			else
				params[i].param_size = 4;
		}
		else if (params[i].param_size == 3)
			params[i].param_size = 2;
		nbparam--;
		i++;
	}
}

void	get_param_data(t_param *params, int nbparam, char *data, int pc)
{
	int		i;
	int		take;

	i = 0;
	take = -1;
	while (++take < params[0].param_size)
		params[i].param_data[take] = data[pc + 1 + take];
	i++;
	while (i < nbparam)
	{
		take = -1;
		while (++take < params[i].param_size)
			params[i].param_data[take] = data[pc + 1 +
			params[i - 1].param_size + take];
		params[i].param_size += params[i - 1].param_size;
		i++;
	}
}
