/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:46:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/30 23:49:43 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static size_t	size_full(t_aolist *aolist)
{
	size_t		size;

	size = 0;
	while (aolist)
	{
		if ((aolist->tok && aolist->tok->type & DOT)
				|| (aolist->tok && aolist->tok->type & LABEL 
				&& aolist->tok->next == NULL))
			;
		else
		{
			aolist->mem_addr = size;
			size += aolist->size;
		}
		aolist = aolist->next;
	}
	return (size);
}

int		syntax_analysis(t_env *e, t_aolist *aolist)
{
	t_aolist	*head;
	t_token		*curr;
	int			ret;

	ret = 0;
	while (aolist && aolist->tok == NULL)
		aolist = aolist->next;
	e->size = size_full(aolist);
	if ((ret = asm_syntax_header(e, aolist)) > 0)
		return (ret);
	aolist = aolist->next->next;
	head = aolist;
	if (aolist == NULL)
		return (syntax_error(e, E_OPC, NULL, 0));
	while (aolist)
	{
		curr = aolist->tok;
		if (curr && curr->type & LABEL)
		{
			curr = curr->next;
			asm_syntax_labelled(e, head);
		}
		if (curr)
		{
			asm_syntax_op(e, aolist, curr);
			asm_syntax_arg(e, aolist, curr->next);
		}
		aolist = aolist->next;
	}
	return (0);
}
