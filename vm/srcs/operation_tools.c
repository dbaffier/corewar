/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:05:26 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/21 01:24:37 by bmellon          ###   ########.fr       */
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
		params_type[i].param_ = param_len;
		types = types << 2;
		i++;
	}
}

void	get_params_len(t_param *params, int nbparam, char type)
{

	get_types(type, params);
	i = 0;
	while (nbparam > 0)
	{
		if (params[i]->param_type == 1)
			params[i]->param_size = 1;
		else if (params[i]->param_type == 2)
			params[i]->param_size = 4;
		else if (params[i]->param_type == 3)
			params[i]->param_size = 2;
		nbparam--;
		i++;
	}
}

void	get_param_data(t_param params, int nbparam, char *data, int pc)
{
	int		i;
	int		take;
	int		len;

	len = 0;
	i = 0;
	while (take < params.param_size)
		params[i].param_data = data[pc + 1 + take++];
	while (i < nbparam - 1)
	{
		take = 0;
		while (take < params[i].param_size)
		{
			params[i].param_data = data[
		}	
	}
}