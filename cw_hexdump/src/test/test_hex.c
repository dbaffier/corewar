
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void	ft_putnbr(int nb)
{
	int tmp;
	if (nb == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		nb = 147483648;
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb <= 9)
	{
		tmp = nb + 48;
		write(1, &tmp, 1);
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

int main(int ac, char **av)
{
	unsigned char buff;
	char *print;
	int fd = open(av[1], O_RDONLY);
	int ret = 0;
	unsigned char mod;
	int len = 0;

	while ((ret = read(fd, &buff, 1)) > 0)
	{
		ft_putnbr(buff);
		if (buff != '0')
			write(1, " ", 2);
		/*while (buff > 0)
		{
			mod = buff % 16;
			if (mod > 9)
				print[len] = 65 + (mod - 10);
			else
				print[len] = mod + 48;
			print[len] = mod;
			len++;
			buff /= 16;
		}*/
	}
	close(fd);
	/*len--;
	int tmp_len = len;
	while (print[len])
	{
		if (len % 2 == 0 && len != tmp_len)
			write(1, " ", 1);
		write(1, &print[len], 1);
		len--;
	}*/
	return (0);
}
