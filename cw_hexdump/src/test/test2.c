
#include <unistd.h>
#include <fcntl.h>

int		main(void)
{
	int bin;
	int fd;
	int len;
	int mod = 0;

	fd = open("test2", O_RDWR);
	bin = 6;
	len = 15;
	while (len >= 0)
	{
		lseek(fd, len, SEEK_SET);
		write(fd, &bin, 1); 
		len--;
	}
	close(fd);
	return (0);
}
