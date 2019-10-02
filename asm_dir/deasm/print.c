
#include "deasm.h"
#include "cw_hexdump.h"

static void		dsprint_path(t_info *inf)
{
	if (inf->e->flag & FLAG_GP)
		ft_printf("%s/%s\n", getcwd(NULL, 0), inf->ds_name);
	else
		ft_printf("%s\n", getcwd(NULL, 0), inf->ds_name);
}

static void		dsprint_dasho(t_info *inf)
{
	ft_printf("%s created, you can now use it to recompile or else.\n", inf->ds_name);
}

void			dsflag_print(t_info *inf)
{
	if (inf->e->flag & FLAG_P || inf->e->flag & FLAG_GP)
		dsprint_path(inf);
	if (inf->e->flag & FLAG_O)
		dsprint_dasho(inf);
}

void			dswrite_warning(t_info *inf)
{
	ft_dprintf(inf->ds_fd, "#Warning : this is a cracked .s file.\n#You will not find label name(s) but this works perfectly as the original .s file\n\n");
}

void			dsprint_err(int error, char *file)
{
	if (error == DS_ERR_EXTENSION)
		ft_dprintf(2, "Usage : ./asm -d [file.cor, file1.cor, ...]\n");
	if (error == DS_ERR_OPEN)
		ft_dprintf(2, "Can't open file : %s\n", file);
	if (error == DS_ERR_MALLOC)
		ft_dprintf(2, "Malloc failed - 404 memory not found\n");
	exit(1);
}
