/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_corfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:28:27 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 20:45:33 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static char		*add_extention(char *basename, int pos)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		basename[pos] = COR_EXT[i];
		i++;
		pos++;
	}
	basename[pos] = '\0';
	return (basename);
}

static int		basename_len(char *file)
{
	int			extension_len;
	int			len;

	len = ft_strlen(file);
	extension_len = 0;
	while (file && len--)
	{
		if (file[len] == '.')
			break ;
		extension_len++;
	}
	return (len - extension_len);
}

static char		*basename(char *file)
{
	int			len;
	int			i;
	char		*b_name;

	len = basename_len(file) + 1;
	i = 0;
	if (!(b_name = (char *)ft_memalloc(sizeof(char) * len + 4 + 1)))
		return (NULL);
	while (file && i < len)
	{
		b_name[i] = file[i];
		i++;
	}
	return (add_extention(b_name, i));
}

static char		*get_fname(char *file)
{
	int occ;

	if ((occ = ft_count_occ(file, '/')) > 0)
	{
		while (occ)
		{
			if (*file == '/')
				occ--;
			file++;
		}
		return (file);
	}
	return (file);
}

int				create_corfile(t_data *data, char *file)
{
	char		*b_name;
	int			fd;

	file = get_fname(file);
	if ((b_name = basename(file)) == NULL)
		return (ERR_MALLOC);
	data->file_name = b_name;
	if ((fd = open(b_name, O_CREAT | O_TRUNC | O_RDWR, 0700)) < 0)
		return (ERR_OPEN);
	free(b_name);
	return (fd);
}
