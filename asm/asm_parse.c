/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 01:48:11 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/20 02:05:29 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "asm.h"

static int token_lst(t_env *e)
{
	static int	c = 0;
	int			ret;
	t_aolist	*lst;
	t_aolist	*new;
	char		*line;

	ret = 0;
	line = NULL;
	if (!(lst = ft_memalloc(sizeof(t_aolist))))
		return (ERR_MALLOC);
	e->aolist = lst;
	while ((ret = get_next_line(e->fd, &line)) > 0)
	{
		if (line && line[0] != '\0')
		{
			if (c == 0 && ++c)
			{
				if ((tok_create(lst, line)) > 0)
					return (ERR_MALLOC);
			}
			else
			{
				new = ft_memalloc(sizeof(t_aolist));
				if ((tok_create(new, line)) > 0)
					return (ERR_MALLOC);
				push_front(lst, new, 0);
			}
		}
		free(line);
	}
	return (0);
}

int		parser(t_env *e, char *file)
{
	int		ret;

	if ((ret = asm_file_open(e, file)) > 1)
		return (ret);
	if ((ret = token_lst(e)) > 0)
		return (ERR_MALLOC);
	for (t_aolist *p = e->aolist; p; p = p->next)
	{
		for (t_token *t = p->tok; t; t = t->next)
			printf("[%s] with type [%d]\n", t->val, t->type);
		ft_printf("new aolist\n");
	}
	return (0);
}
