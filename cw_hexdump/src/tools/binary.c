/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:00:51 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 02:17:26 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static int		len_binary(char dec)
{
	int	len;

	len = 0;
	while (dec > 0)
	{
		dec /= 2;
		len++;
	}
	return (len);
}

static char		*str_binary(char dec)
{
	int		i;
	char	*stock;

	i = 0;
	if (!(stock = (char *)malloc(sizeof(char) * len_binary(dec) + 2)))
		return (NULL);
	while (dec > 0)
	{
		stock[i] = (dec % 2) + 48;
		i++;
		dec = dec / 2;
	}
	stock[i] = '\0';
	return (stock);
}

short			binary(char dec)
{
	int		i;
	short	bin;
	char	*stock;

	bin = 0x0;
	if (!(stock = str_binary(dec)))
		return (ERR_MALLOC);
	i = ft_strlen(stock) - 1;
	while (stock && stock[i] && i >= 0)
	{
		if (stock[i] == 49)
			bin |= 1;
		bin <<= 1;
		i--;
	}
	bin >>= 1;
	free(stock);
	return (bin);
}
