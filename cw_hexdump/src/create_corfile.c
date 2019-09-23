/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_corfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:28:27 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/24 00:49:56 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static char		*add_extention(char *basename, int pos)
{
	int			i;

	i = 0;
	while (i <= 3)
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

	len = basename_len(file);
	i = 0;
	if (!(b_name = (char *)malloc(sizeof(char) * len + 4 + 1)))
		return (NULL);
	while (file && i < len + 1)
	{
		b_name[i] = file[i];
		i++;
	}
	return (add_extention(b_name, i));
}

int				create_corfile(char *file)
{
	char		*b_name;
	int			fd;

	if ((b_name = basename(file)) == NULL)
		return (ERR_MALLOC);
	if ((fd = open(b_name, O_CREAT | O_RDWR, 0700)) < 0)
		return (ERR_OPEN);
	return (fd);
}
