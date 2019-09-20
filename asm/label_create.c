/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:05:46 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/20 03:32:18 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include "ft_printf.h"


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

int		create_label(t_token **head, char *val, size_t *i)
{
	t_token		*ptr;
	t_token		*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	if (!(new->val = dup_val(val, i)))
		return (ERR_MALLOC);
	new->type = LABEL;
	if (*head == NULL)
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (0);
}

int		create_dot(t_token **head, char *val, size_t *i)
{
	t_token		*ptr;
	t_token		*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	if (!(new->val = dup_val(val, i)))
		return (ERR_MALLOC);
	new->type = DOT;
	if (*head == NULL)
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (0);
}

int		is_label(char *line, int start)
{
	while (line[start] && line[start] != ' ' && line[start] != '\t')
		start++;
	if (line[start - 1] == ':')
		return (1);
	return (0);
}
