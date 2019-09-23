/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:51:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/09/23 19:51:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "vm.h"
#include "libft.h"

static uint32_t	byteswap_32(uint32_t x)
{
	return (((x & 0xff000000u) >> 24) | ((x & 0x00ff0000u) >> 8)
		| ((x & 0x0000ff00u) << 8) | ((x & 0x000000ffu) << 24));
}

static int		get_data(int fd, t_process *proc)
{
	ssize_t		ret;
	size_t		off;
	char		buff[1024];

	off = 0;
	while ((ret = read(fd, buff, sizeof(buff))) > 0)
	{
		ft_memcpy((char *)proc->file + off, buff, ret);
		off += ret;
	}
	if (ret)
		return (ERR_READ);
	if (off <= sizeof(t_header))
		return (ERR_SIZE_LOW);
	if (byteswap_32(((t_header *)proc->file)->magic) != COREWAR_EXEC_MAGIC)
		return (ERR_MAGIC);
	off -= sizeof(t_header);
	if (off != byteswap_32(((t_header *)proc->file)->prog_size))
		return (ERR_SIZE_DIFF);
	if (off > CHAMP_MAX_SIZE)
		return (ERR_SIZE_HIGH);
	proc->data_size = off;
	return (IS_OK);
}

static int		get_player_data(t_process *proc)
{
	int			fd;
	off_t		ret;

	ret = IS_OK;
	if ((fd = open(proc->name, O_RDONLY)) < 0)
		ret = ERR_OPEN;
	else if ((proc->file_size = lseek(fd, 0, SEEK_END)) < 0)
		ret = ERR_LSEEK;
	else if ((proc->file = malloc(proc->file_size)) == NULL)
		ret = ERR_MALLOC;
	else if (lseek(fd, 0, SEEK_SET) < 0)
		ret = ERR_LSEEK;
	else
		ret = get_data(fd, proc);
	if (fd >= 0)
		close(fd);
	return (ret);
}

static int		check_id(t_process *proc, int *id)
{
	t_process	*tmp;

	tmp = proc;
	if (*id)
		while (proc)
		{
			if (proc->id == *id)
				return (ERR_NUMBER);
			proc = proc->next;
		}
	else
		while (tmp)
		{
			if (tmp->id == *id)
			{
				(*id)++;
				tmp = proc;
			}
		}
	return (IS_OK);
}

int				get_player(t_env *e, char *av)
{
	t_process	*tmp;

	if (e->nb_players >= MAX_PLAYERS)
		return (ERR_MAX_CHAMP);
	if (check_id(e->proc, &e->id))
		return (ERR_NUMBER);
	tmp = e->proc;
	if ((e->proc = ft_memalloc(sizeof(*e->proc))) == NULL)
	{
		e->proc = tmp;
		return (ERR_MALLOC);
	}
	e->proc->id = e->id;
	e->proc->name = av;
	e->proc->next = tmp;
	e->id = 0;
	e->nb_players++;
	return (get_player_data(e->proc));
}
