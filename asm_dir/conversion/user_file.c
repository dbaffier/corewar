
#include "cw_hexdump.h"
#include "asm.h"

int		user_file(t_data *data)
{
	int len;

	if ((len = ft_strlen(data->e->fd_user)) > 128)
	{
		free(data->e->fd_user);
		ft_printf("File name too big ... Why would you create a file this big ? %d\n", len);
		exit(1);
	}
	data->file_name = ft_strdup(data->e->fd_user);
	data->file_name = ft_strjoinfree(data->file_name, ".cor", 1);
	free(data->e->fd_user);
	if ((data->fd = open(data->file_name, O_CREAT | O_TRUNC | O_RDWR), 0700) < 0)
		return (ERR_OPEN);
	return (0);
}

int		parse_dashs(t_env *e, char **av, int i)
{
	if (e->flag & FLAG_S)
	{
		if (av[i][0] == '\0')
		{
			ft_printf("Ouch, you forgot your file name. We could have seg fault !\n");
			exit(1);
		}
		e->fd_user = ft_strdup(av[i]);
		return (i + 1);
	}
	return (i);
}
