/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:52:15 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/20 03:33:20 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		dump(char *file, void *addr, int len)
{
	char	*pc;
	int		i;

	i = 0;
	pc = (char *)addr;
	if (file)
		ft_printf("%s:\n", file);
	if (len < 0 || len == 0)
		ft_printf("invalid len : %d\n", len);
	while (pc && pc[i])
	{
		ft_printf("%x", pc[i]);
		ft_printf(" ");
		if ((i + 1) % 16 == 0)
			ft_printf("\n");
		else if ((i + 1) % 8 == 0)
			ft_printf("\t");
		i++;
	}
}

int		main(void)
{
	char str[] = "truc un peu long parce quil en faut bien un";

	dump("str", &str, sizeof(str));
	return (0);
}
