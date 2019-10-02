/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 00:06:19 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/02 00:58:58 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"
#include "cw_hexdump.h"

static char	*get_path(char *file)
{
	int i;
	int len;
	char *path;

	len = len_path(file);
	path = NULL;
	i = 0;
	if (len > 0)
	{
		if (!(path = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (i < len)
		{
			path[i] = file[i];
			i++;
		}
		path[i] = '\0';
	}
	return (path);
}

void			dsflag_print(t_info *inf)
{
	char *path;

	path = get_path(inf->ds_name);
	if (inf->e->flag & FLAG_P || inf->e->flag & FLAG_GP)
	{
		if (inf->e->flag & FLAG_GP)
			ft_printf("%s/%s\n", getcwd(NULL, 0), inf->ds_name);
		else
			ft_printf("%s/%s\n", getcwd(NULL, 0), path);
	}
	if (inf->e->flag & FLAG_O)
		ft_printf("%s created, you can now use it to recompile or else.\n", inf->ds_name);
	free(path);
}

void			dswrite_warning(t_info *inf)
{
	ft_dprintf(inf->ds_fd, "#Warning : this is a cracked .s file.\n");
	ft_dprintf(inf->ds_fd, "#You will not find label name(s) but this works perfectly as the original .s file\n\n");
}

void			dsprint_err(int error, char *file)
{
	if (error == DS_ERR_EXTENSION)
		ft_dprintf(2, "Usage : ./asm -d [file.cor, file1.cor, ...]\n");
	if (error == DS_ERR_OPEN)
		ft_dprintf(2, "Can't open file : %s\n", file);
	if (error == DS_ERR_MALLOC)
		ft_dprintf(2, "Malloc failed - 404 memory not found\n");
	exit(1);
}
