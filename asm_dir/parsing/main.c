/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:15:33 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/28 01:16:39 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

static int	err_file(int err)
{
	static char *tab_err[] = { NULL, ERR_STR_FILE,
		ERR_STR_EXTENSION, ERR_STR_NOFILE, ERR_STR_OVERFLOW , };

	ft_dprintf(2, "%s\n", tab_err[err]);
	ft_dprintf(2, "Usage : ./asm file.s\n");
	return (1);
}

int main(int ac, char **av)
{ 
	t_env		e;
	int			ret;
	int			i;

	ret = 0;
	ft_memset(&e, 0, sizeof(e));
	i = parse_flag(&e, av);
	if ((ret = asm_file(ac, av, i)) > 0)
		return (err_file(ret));
	if ((ret = parser(&e, av[i])) > 0)
		return (0);
	if ((ret = dump_to_file(&e)) > 0)
		return (0);
	return (0);
}
