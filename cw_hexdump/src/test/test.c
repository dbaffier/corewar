/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:49:39 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/21 22:58:55 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	unsigned char c = -11;
	long t = (long)-c;
	char *str;
	int i;

	printf("%ld\n", -c);
	printf("%ld\n", t);
	str = malloc(1000);
	while (t > 0)
	{
		str[i] = t % 2 + 48;
		t /= 2;
		i++;
	}
	str[i] = '\0';
	int len = strlen(str);
	int bin = 0;
	while (len >= 0)
	{
		if (str[len] == 49)
			bin |= 1;
		if (len % 8 == 0 && len != strlen(str))
		{
			write(1, &bin, 1);
			bin = 0;
		}
		len--;
		bin <<= 1;
	}
	return (0);
}
