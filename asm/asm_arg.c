/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:40:14 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/23 00:58:00 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

static void		parse_splited(t_token *ptr, char *str)
{
	if (str[0] == 'r')
	{
		ptr->val = ft_atoi(str + 1);
		ptr->type = T_REG;
	}
	else if (str[0] == DIRECT_CHAR)
	{
		if (str[1] == LABEL_CHAR)
		{
			ptr->lab = str + 2;
			ptr->type = T_DIR | T_LAB;
		}
		else
		{
			ptr->val = ft_atoi(str + 1);
			ptr->type = T_DIR;
		}
	}
	else if (str[0] == LABEL_CHAR)
	{
		ptr->lab = str + 1;
		ptr->type = T_IND | T_LAB;
	}
	else
	{
		ptr->val = ft_atoi(str);
		ptr->type = T_IND;
	}
}

static int		parse_arg(t_token *ptr, char **splited)
{
	size_t		i;
	t_token		*save;

	i = 0;
	save = ptr;
	while (splited[i])
	{
		parse_splited(ptr, splited[i]);
		i++;
	}
	return (0);
}

int		grep_arg(t_token *ptr, char *line, size_t *i)
{
	size_t		j;
	t_token		*save;
	char		**arg;
	char		**splited;

	j = 0;
	save = ptr;
	if ((arg = ft_strsplit(&line[*i], ',')) == NULL)
		return (ERR_MALLOC);
	while (arg[j])
	{
		splited = ft_strsplitws(arg[j]);
		parse_arg(ptr, splited);
		if (arg[j + 1])
		{
			if (!(ptr->next = ft_memalloc(sizeof(t_token))))
				return (ERR_MALLOC);
			ptr = ptr->next;
		}
		free(splited);
		j++;
	}
	ptr->arg_n = j;
	ft_freetab(&arg);
	while (line[*i])
		*i = *i + 1;
	return (0);
}

