/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 01:48:11 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/28 20:41:46 by dbaffier         ###   ########.fr       */
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
		e->line = e->line + 1;
		if (line && line[0] != '\0')
		{
			if (c == 0 && ++c)
			{
				lst->line = e->line;
				if ((tok_create(lst, &line)) > 0)
					return (ERR_MALLOC);
			}
			else
			{
				new = ft_memalloc(sizeof(t_aolist));
				new->line = e->line;
				if ((tok_create(new, &line)) > 0)
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
	/*for (t_aolist *o = e->aolist; o; o = o->next)
	{
		printf("-------aolist------\n");
		for(t_token *t = o->tok; t; t = t->next)
		{
			printf("\t tok->lab : [%s]\n", t->lab);
			printf("\t tok->val : [%d]\n", t->val);
		}
	}*/
	if ((ret = syntax_analysis(e, e->aolist)) > 0)
		return (ERR_MALLOC);
	return (0);
}
