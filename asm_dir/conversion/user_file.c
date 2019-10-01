/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:09:01 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/02 01:43:14 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"
#include "asm.h"

static char *cut_path(char *file)
{
	int		len;
	int		len_p;
	int		i;
	char	*without_path;

	len = ft_strlen(file);
	len_p = len_path(file);
	i = 0;
	if (!(without_path = (char *)malloc(sizeof(char) * (len - len_p) + 1)))
		return (NULL);
	while (file[len_p])
	{
		without_path[i] = file[len_p];
		i++;
		len_p++;
	}
	without_path[i] = '\0';
	return (without_path);
}

int		user_file(t_data *data)
{
	int		len;
	char	*b_name;

	if ((len = ft_strlen(data->e->fd_user)) > 128)
	{
		free(data->e->fd_user);
		ft_printf("File name too big ... Why would you create a file this big ? %d\n", len);
		exit(1);
	}
	data->file_name = ft_strdup(data->e->fd_user);
	if (data->e->flag & FLAG_F)
	{
		if (data->file_name[0] == '.')
			data->file_name = getcwd(NULL, 0);
		data->file_name = ft_strjoinfree(data->file_name, "/", 1);
		b_name = cut_path(basename(data->e->fd_name));
		data->file_name = ft_strjoinfree(data->file_name, b_name, 3);
	}
	else
		data->file_name = ft_strjoinfree(data->file_name, ".cor", 1);
	free(data->e->fd_user);
	if ((data->fd = open(data->file_name, O_CREAT | O_TRUNC | O_RDWR, 0700)) < 0)
		return (ERR_OPEN);
	return (0);
}

int		get_user_entry(t_env *e, char **av, int i)
{
	if (e->flag & FLAG_S && e->flag & FLAG_F)
	{
		ft_printf("Incompatible flags : -s, -f\n");
		exit(0);
	}
	if (e->flag & FLAG_S || e->flag & FLAG_F)
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
