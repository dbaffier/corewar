/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:00:51 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 00:59:24 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static int		len_binary(char c)
{
	int	len;

	len = 0;
	while (c > 0)
	{
		c /= 2;
		len++;
	}
	return (len);
}

static char		*str_binary(char c)
{
	int		i;
	char	*stock;

	i = 0;
	if (!(stock = (char *)malloc(sizeof(char) * len_binary(c) + 1)))
		return (NULL);
	while (c > 0)
	{
		stock[i] = (c % 2) + 48;
		i++;
		c = c / 2;
	}
	stock[i] = '\0';
	return (stock);
}

short			binary(char c)
{
	int		i;
	short	bin;
	char	*stock;

	bin = 0x0;
	if (!(stock = str_binary(c)))
		return (ERR_MALLOC);
	i = ft_strlen(stock) - 1;
	while (stock[i] && i >= 0)
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
