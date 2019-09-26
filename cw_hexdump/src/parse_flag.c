
#include "cw_hexdump.h"

void		print_usage(int error)
{
	ft_dprintf(2, "usage: ./asm [-n] [file ...]\n");
	exit(0);
}

int			set_msk(t_data *data, char c)
{
	t_flags	tab[1] = {DASH_N};
	int		i;

	while (i < sizeof(tab) / sizeof(tab[i]))
	{
		if (c == tab[i].opt)
		{
			data->flag |= FLAG_N;
			return (1);
		}
		i++;
	}
	return (0);
}

int			parse_flag(t_data *data, char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' && av[i][j + 1] == '-')
				return (0);
			if (j == 0 && av[i][j] != '-')
				return (ERR_FLAG);
			if (j != 0 && av[i][j] == '-')
				return (ERR_FLAG);
			if (av[i][j] != '-')
				if (set_msk(data, av[i][j]) == 0)
					return (ERR_FLAG);
			j++;
		}
		i++;
	}
	return (0);
}
