/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:09:58 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/26 21:31:11 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void	print_path(t_data *data)
{
	if (data->flag & FLAG_GP)
		ft_printf("%s/%s\n", getcwd(NULL, 0), data->file_name);
	else
		ft_printf("%s\n", getcwd(NULL, 0));
}
