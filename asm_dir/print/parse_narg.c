
#include "asm.h"
#include "cw_hexdump.h"

static void	print_errarg(t_env *e, int narg)
{
	if (narg > 2)
		ft_dprintf(2, "Error : too many arguments\n");
	else
		ft_dprintf(2, "Error : not enough argument\n");
	if (e->flag & FLAG_S && e->flag & FLAG_F)
		ft_dprintf(2, "Usage : asm -s [name] [file.s]\n\tasm -f [path] [file.s]\n");
	else if (e->flag & FLAG_S)
		ft_dprintf(2, "Usage : asm -s [name] [file.s]\n");
	else if (e->flag & FLAG_F)
		ft_dprintf(2, "Usage : asm -f [path] [file.s]\n");
	exit(1);
}

void		parse_narg(t_env *e, int ac, int i)
{
	int n_arg;

	n_arg = ac - i;
	if (e->flag & ATLST_ONE && n_arg < n_arg + 1)
	{
		ft_dprintf(2, "Error : Not enough argument\n");
		ft_dprintf(2, "Usage : asm [-Pdfnops] [file, ...]\n");
		exit(1);
	}
	if (e->flag & FLAG_S && e->flag & FLAG_F)
	{
		ft_dprintf(2, "Incompatible flags : -s, -f ; sees -h, --help\n");
		exit(1);
	}
	if (e->flag & FLAG_S || e->flag & FLAG_F)
	{
		if ((ac - i) != 2)
			print_errarg(e, ac - i);
		if (e->flag & FLAG_P)
			e->flag &= ~FLAG_P;
		if (e->flag & FLAG_GP)
			e->flag &= ! FLAG_GP;
	}
	if (e->flag & FLAG_D)
	{
		if (e->flag & FLAG_N)
			e->flag &= ~FLAG_N;
		if (e->flag & FLAG_S)
			e->flag &= ~FLAG_S;
		if (e->flag & FLAG_F)
			e->flag &= ~FLAG_F;
	}
}
