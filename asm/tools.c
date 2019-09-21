/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:09:46 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/20 21:40:22 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

char	*str_s_e(char *line, int s, int e)
{
	size_t		i;
	char		*new;

	i = 0;
	if (!(new = malloc(sizeof(char) * (e - s) + 1)))
		return (NULL);
	while (line[s] && s <= e)
	{
		new[i] = line[s];
		s++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

void		ft_freetab(char ***table)
{
	size_t		i;

	i = 0;
	if (table)
		if (*table)
		{
			while ((*table)[i])
			{
				free((*table)[i]);
				(*table)[i] = NULL;
				i++;
			}
			free(*table);
			*table = (char **)0;
		}
}

void	push_front(void *head, void *new, int type)
{
	t_token		*ptrr;
	t_aolist	*ptr;

	ptr = NULL;
	ptrr = NULL;
	if (type == 1)
	{
		ptrr = (t_token *)head;
		while (ptrr->next)
			ptrr = ptrr->next;
		ptrr->next = (t_token *)new;
	}
	else
	{
		ptr = (t_aolist *)head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = (t_aolist *)new;
	}
}
