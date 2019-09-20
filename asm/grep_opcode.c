/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grep_opcode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:25:39 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/20 02:17:02 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

static char		*dup_val(char *line, size_t *i)
{
	char		*new;
	size_t		s;
	size_t		e;

	s = *i;
	e = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
		*i = *i + 1;
	if (!(new = malloc(sizeof(char) * (*i - s) + 1)))
		return (NULL);
	while (line[s] && s < *i)
	{
		new[e] = line[s];
		s++;
		e++;
	}
	new[e] = '\0';
	return (new);
}

static int		grep_arg(t_token *ptr, char *line, size_t *i)
{
	size_t		j;
	size_t		k;
	char		**arg;
	char		**splited;

	j = 0;
	k = 0;
	if ((arg = ft_strsplit(&line[*i], ',')) == NULL)
		return (ERR_MALLOC);
	while (arg[j])
	{
		splited = ft_strsplit(arg[j], ' ');
		while (splited[k])
		{
			ptr->val = *splited;
			ptr->type = PARAM;
			if (!(ptr->next = ft_memalloc(sizeof(t_token))))
				return (ERR_MALLOC);
			ptr = ptr->next;
			k++;
		}
		j++;
	}
	ft_freetab(&arg);
	while (line[*i])
		*i = *i + 1;
	return (0);
}

int		grep_opcode(t_token **head, char *line, size_t st, size_t *i)
{
	t_token		*new;
	t_token		*curr;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	if (!(new->val = dup_val(line, i)))
		return (ERR_MALLOC);
	if (!(new->next = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	if (grep_arg(new->next, line, i) > 0)
		return (ERR_MALLOC);
	if (*head == NULL)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (0);
}
