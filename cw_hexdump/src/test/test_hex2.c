#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"


int len_buff(char buff, int base)
{
	int len;

	len = 0;
	while (buff > 0)
	{
		buff = buff / base;
		len++;
	}
	return (len);
}

void conv_nbr(int base, int n, char letter)
{
	if (n <= base - 1)
	{
		if (n <= 9)
			printf("%c", n + 48);
		else
			printf("%c", (n - 10) + letter);
	}
	if (n > base - 1)
	{
		conv_nbr(base, n / base, letter);
		conv_nbr(base, n %  base, letter);
	}
}
char *dump(int fd)
{
	char *str;
	char *tmp;
	unsigned char buff;

	str = NULL;
	tmp = NULL;
	while (read(fd, &buff, 1) > 0)
	{
		//ft_printf("%x\t", buff);
		conv_nbr(16, buff, 97);

/*
		if (!str)
			str = ft_convert_base(buff, 16, len_buff(buff, 16), 65);
		else
		{
			tmp = ft_convert_base(buff, 16, len_buff(buff, 16), 65);
			str = ft_strjoinfree(str, " ", 0);
			str = ft_strjoinfree(str, tmp, 2);
		}*/
	}
	return (str);
}

int main(int ac, char **av)
{
	int i = 0;
	int fd = open(av[1], O_RDONLY);
	char *str;

	str = dump(fd);
	//printf("%s\n", str);
	close(fd);
	return (0);
}
