#include "libft.h"
#include "ft_printf.h"

int		main(void)
{
	int bin;

	bin = 0x0;

	////indirect
	bin <<= 1;
	bin |= 1;
	bin <<= 1;
	bin |= 1;
	
	////direct
	bin <<= 1;
	bin |= 1;
	bin <<= 1;

	/////registre
	bin <<=2;
	bin |= 1;

	///////end
	bin <<= 2;
	ft_printf("%x\n", bin);
	return (0);
}
