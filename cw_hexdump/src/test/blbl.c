#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int			main(int ac, char **av)
{
	unsigned char buff;

	int fd = open(av[1], O_RDONLY);
	while (read(fd, &buff, 1))
	{
		printf("%x", buff);
	}
	return (0);
}
