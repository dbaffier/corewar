/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:38:45 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/20 01:16:11 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

/*static short	hex_to_bin(char *type)
{		

}*/

void			reverse_type(char *type)
{
	int bin;

	bin = type;
	printf("%x\n", bin);
}

int			main(void)
{
	reverse_type("e4");
	return (0);
}
