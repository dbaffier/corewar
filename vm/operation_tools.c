#include "vm.h"

void	get_params_len(char *arg_type, t_type params, int nbparam)
{
	int		index;

	index = nbparam - 1;
	while (nbparam > 0)
	{
		if (arg_type[index] & T_REG)
			params[index].param_size = 1;
		else if (arg_type[index] & T_DIR)
			params[index].param_size = 2;
		else if (arg_type[index] & T_IND)
			params[index].param_size = 4;
		else if (arg_type[index] & T_LAB)
			params[index].param_size = 8;
		nbparam--;
		index--;
	}
	return (params);
}

void	get_params_data(t_op *op, int *params, int nbparams, char *data)
{
	
}