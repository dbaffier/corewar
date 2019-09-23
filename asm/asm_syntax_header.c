/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 00:59:21 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/23 02:48:43 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

int		asm_syntax_header(t_env *e, t_aolist *head)
{
	t_token		*ptr;
	t_token		*ptr2;

	ptr = head->tok;
	ptr2 = head->next->tok;
	if (ft_strcmp(ptr->lab, NAME_CMD_STRING))
		return (syntax_error(e, ERR_NAME_H, ptr, head->line));
	if (ptr->next)
	{
		if (ptr->next->lab && ft_strlen(ptr->next->lab) > 128)
			return (syntax_error(e, ERR_NAME_LEN, ptr->next, head->next->line));
	}
	else
		return (syntax_error(e, ERR_NAME_H, ptr, head->line));
	if (ft_strcmp(ptr2->lab, COMMENT_CMD_STRING))
		return (syntax_error(e, ERR_COMMENT_H, ptr2, head->next->line));
	if (ptr2->next)
	{
		if (ptr2->next->lab && ft_strlen(ptr2->next->lab) > 2048)
			return (syntax_error(e, ERR_COMMENT_LEN, ptr2->next, head->next->line));
	}
	else
		return (syntax_error(e, ERR_COMMENT_H, ptr2, head->next->line));
	return (0);
}
