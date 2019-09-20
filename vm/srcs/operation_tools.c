/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:05:26 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/20 21:55:49 by bmellon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_params_len(t_type *params, int nbparam)
{
	int		index;

	index = nbparam - 1;
	while (nbparam > 0)
	{
		if (params[index].param_data & T_REG)
			params[index].param_size = 1;
		else if (params[index].param_data & T_DIR)
			params[index].param_size = 2;
		else if (params[index].param_data & T_IND)
			params[index].param_size = 4;
		else if (params[index].param_data & T_LAB)
			params[index].param_size = 8;
		nbparam--;
		index--;
	}
	return (params);
}

void	get_reg_data(t_type *params, int nbparam, char *data, int pc)
{
	int		i;
	int		take;
	int		len;

	len = 0;
	i = 0;
	while (i < nbparam - 1)
	{
		take = 0;
		if (i > 0)
			len = params[i].param_size;
		while (take < params[i].param_size)
		{
			params[i].param_data = data[
		}	
	}
}