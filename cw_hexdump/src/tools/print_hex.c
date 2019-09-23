
#include "cw_hexdump.h"

void	nprint_nb(t_data *data, int base, unsigned char n, char letter)
{
	if (n <= base - 1)
	{
		if (n <= 9)
			
	}
}

void	print_hex(t_data *data)
{
	unsigned char buff;

	while (read(data->fd, &buff, 1) > 0)
		nprint_nb(data, 16, buff, 97);
}
