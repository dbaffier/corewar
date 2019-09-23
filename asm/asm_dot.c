/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:02:04 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/23 00:50:46 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "ft_printf.h"

static char		*dup_dot(char *line, size_t *i)
{
	char		*new;
	size_t		s;
	size_t		e;

	s = *i;
	e = 0;
	while (line[*i] && line[*i] != '\"' && line[*i] != '\t' && line[*i] != ' ')
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

static char	*dup_all(char *val, size_t *i)
{
	char		*new;
	size_t		s;
	size_t		e;

	s = *i;
	e = 0;
	while (val[*i] && val[*i] != '\"')
		*i = *i + 1;
	*i = *i + 1;
	if (!(new = malloc(sizeof(char) * (*i - s) + 1)))
		return (NULL);
	while (val[s] && s < (*i - 1))
	{
		new[e] = val[s];
		s++;
		e++;
	}
	new[e] = '\0';
	return (new);
}

int		quoted(char *val, size_t *i)
{
	int		j;
	
	while (val[*i] && (val[*i] == ' ' || val[*i] == '\t'))
		*i = *i + 1;
	if (val[*i] == '\"')
	{
		*i = *i + 1;
		j = *i;
		while (val[j])
		{
			if (val[j] == '\"')
			{
				j++;
				while (val[j] && (val[j] == ' ' || val[j] == '\t'))
					j++;
				if (val[j] == '\0')
					return (1);
				else
					return (0);
			}
			j++;
		}
		return (0);
	}
	else
		return (0);
}

int		create_dot(t_token **head, char *val, size_t *i)
{
	t_token		*ptr;
	t_token		*new;
	t_token		*next;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	new->lab = dup_dot(val, i);
	new->type = DOT;
	if (!(next = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	next->lab = quoted(val, i) ? dup_all(val, i) : NULL;
	next->type = DOT_ARG;
	new->next = next;
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
