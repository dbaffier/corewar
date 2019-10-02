/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:09:01 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/02 16:45:12 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"
#include "asm.h"

static int	count_moveup(char *file, char *dotdot)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (file[i])
	{
		if (file[i] == '.')
		{
			j = 0;
			while (dotdot[j] == file[i])
			{
				j++;
				i++;
			}
			if (j == 4)
				count++;
		}
		i++;
	}
	return (count);
}

static void trunc_dir(t_data *data, int count_trunc)
{
	int			len;
	int			i;
	int			j;
	static char buff[4096];
	static char buff2[4096];

	getcwd(buff, 4096);
	len = ft_strlen(buff) - 1;
	i = count_trunc * 3;
	j = 0;
	while (buff[len])
	{
		if (count_trunc == 0)
			break;
		else
			buff[len] = '\0';
		if (buff[len] == '/')
			count_trunc--;
		len--;
	}
	while (data->file_name[i])
	{
		buff2[j] = data->file_name[i];
		j++;
		i++;
	}
	if (buff2[0] != '\0')
	{
		free(data->file_name);
		data->file_name = ft_strdup(buff2);
	}
	data->file_name = ft_strjoinfree(buff, data->file_name, 2);
}

static void	handle_dotdot(t_data *data)
{
	if (ft_strcmp(data->file_name, ".") == 0)
		data->file_name = getcwd(NULL, 0);
	if (ft_strcmp(data->file_name, "../") == 0 || ft_strcmp(data->file_name, "..") == 0
			|| count_moveup(data->file_name, "../") > 0)
		trunc_dir(data, count_moveup(data->file_name, "../"));
}

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
		handle_dotdot(data);
		len = ft_strlen(data->file_name);
		if (data->file_name[len - 1] != '/')
			data->file_name = ft_strjoinfree(data->file_name, "/", 1);
		b_name = cut_path(basename(data->e->fd_name));
		data->file_name = ft_strjoinfree(data->file_name, b_name, 3);
		printf("data->file_name bef open = %s\n", data->file_name);
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
