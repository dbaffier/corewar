/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:31:42 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/18 22:55:17 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

int		create_dot(t_token **head, char *val, size_t *i)
{
	t_token		*ptr;
	t_token		*new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	*i = *i + 1;
	new->val = val;
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
}
