
#include "asm.h"
#include "ft_printf.h"

void	asm_helper(void)
{
	ft_printf("NAME\n");
	ft_printf("\tasm, best version\n\n");
	ft_printf("SYNOPSIS\n");
	ft_printf("\tusage : asm [-Ponp] [-f path] [-s name] file.s ...\n\t\t[-d] file.cor ...\n\n");
	ft_printf("DESCRIPTION\n");
	ft_printf("\tasm is a program compiling .s file to .cor in purpose to use it in a corewar arena.\n\n");
	ft_printf("\tP\t:  while `f` or `s` disable, print the path to the file created\n");
	ft_printf("\to\t:  if `n` enable, print hexdump offset ; if not print file rights and creation date\n");
	ft_printf("\tn\t:  launch an interactive visu while encoding\n");
	ft_printf("\tp\t:  while `f` or `s` disable, print the path to the file created with the file name\n\n");
	ft_printf("    MUTIPLE FILE DISABLE\n");
	ft_printf("\tFollowing flags will disable multiple file on asm, and they are incompatible together.\n");
	ft_printf("\tUsing `s` with `f` will return an error.\n");
	ft_printf("\tFlags `p` and `P` are disabled here so they will have no action.\n\n");
	ft_printf("\tf path\t:  get the fisrt argument after flags as a directory for the future created file\n");
	ft_printf("\ts name\t:  get the fisrt argument after flags as the name of the future created file\n\n");
	ft_printf("    DEASM\n");
	ft_printf("\tThe flag `d` allow you to send in asm a .cor file, some flags are disable here.\n");
	ft_printf("\tFlags `s`, `f` are not allowed and `n` will have no action.\n\n");
	ft_printf("\td\t:  take a .cor file and create the equivalent .s file with the unique extension .d.s\n\n");
	ft_printf("EXAMPLE\n");
	ft_printf("\t./asm -n file.s\n\n");
	ft_printf("AUTHOR\n");
	ft_printf("\tdbaffier, gbourgeo, bmellon, mmonier, and all the lifesavers on Google (;\n\n");
	ft_printf("SEE ALSO\n");
	ft_printf("\t./vm\n");
	exit(0);
}
