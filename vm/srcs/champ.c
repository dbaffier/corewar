/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:05:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/18 19:17:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"
#include "ft_printf.h"

// int		header_check(void *data, int ret)
// {
// 	char	*filedata;
// 	char	*test;
// 	int		i;

// 	i = 0;
// 	filedata = (char *)data;
// 	while (filedata && filedata[i])
// 	{
// 		test[i] = filedata[i];
// 	}	
// 	return (1);
// 	(void)ret;
	
// }

static int	get_data(int fd, void *data)
{
	int		ret;
	int		off;
	char	buff[1024];

	off = 0;
	while ((ret = read(fd, buff, sizeof(buff))) > 0)
	{
		ft_memcpy((char *)data + off, buff, ret);
		off += ret;
	}
	// ret = header_check(data, ret);
	return (ret);
}

int			get_champions(t_env *e)
{
	int		i;
	int		fd;
	off_t	ret;

	i = 0;
	while (i < e->nb_players)
	{
		fd = open(e->proc[i].name, O_RDONLY);
		if (fd < 0)
			return (corewar_errors(ERR_OPEN, e->proc[i].name, e));
		e->proc[i].size = lseek(fd, 0, SEEK_END);
		if (e->proc[i].size < 0)
			return (corewar_errors(ERR_LSEEK, e->proc[i].name, e));
		e->proc[i].data = malloc(e->proc[i].size);
		if (e->proc[i].data == NULL)
			return (corewar_errors(ERR_MALLOC, e->proc[i].name, e));
		if (lseek(fd, 0, SEEK_SET) < 0)
			return (corewar_errors(ERR_LSEEK, e->proc[i].name, e));
		ret = get_data(fd, e->proc[i].data);
		close(fd);
		if (ret)
			return (corewar_errors(ERR_READ, e->proc[i].name, e));
		i++;
	}
	return (IS_OK);
}
