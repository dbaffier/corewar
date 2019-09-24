/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_label.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:57:32 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/23 18:08:40 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"


t_aolist	*brother_link(t_aolist *head, t_token *curr)
{
	t_token		*ptr;

	while (head)
	{
		ptr = head->tok;
		if (ptr->type == LABEL)
		{
			if (!ft_strcmp(curr->lab, ptr->lab))
				return (head);
		}
		head = head->next;
	}
	return (NULL);
}

static int	lab_val(t_aolist *curr, t_aolist *next)
{
	return (next->mem_addr - curr->mem_addr);
}

int			asm_lexical_label(char *lab)
{
	int		count;
	int		i;
	int		j;
	
	i = 0;
	count = 0;
	while (LABEL_CHARS[i])
	{
		j = 0;
		while (lab[j])
		{
			if (lab[j] == LABEL_CHARS[i])
				count++;
			j++;
		}
		i++;
	}
	if (count != ft_strlen(lab))
		return (1);
	return (0);
}

int			asm_syntax_label(t_env *e, t_aolist *head, t_token *curr)
{
	while (curr)
	{
		if (curr->type & T_LAB)
		{
			if (asm_lexical_label(curr->lab))
				return (syntax_error(e, ERR_LAB, curr, head->line));
			if (!(head->lab = brother_link(head, curr)))
				return (syntax_error(e, ERR_LAB_FOUND, curr, head->line));
			curr->bin = lab_val(head, head->lab);
		}
		curr = curr->next;
	}
	return (0);
}
