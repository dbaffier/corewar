/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 00:59:21 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/30 04:06:02 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

int		asm_syntax_header(t_env *e, t_aolist *head)
{
	t_token		*ptr;
	t_token		*ptr2;

	if (!head)
		return (syntax_error(e, ERR_NAME_H, NULL, 1));
	ptr = head->tok;
	if (ft_strcmp(ptr->lab, NAME_CMD_STRING))
		return (syntax_error(e, ERR_NAME_H, NULL, head->line));
	if (ptr->next)
	{
		if (!ptr->next->lab)
			return (syntax_error(e, ERR_NAMENOTF, NULL, head->next->line));
		if (ptr->next->lab && ft_strlen(ptr->next->lab) > 128)
			return (syntax_error(e, ERR_NAME_LEN, NULL, head->next->line));
	}
	else
		return (syntax_error(e, ERR_NAME_H, NULL, head->line));
	ptr2 = head->next->tok;
	if (ft_strcmp(ptr2->lab, COMMENT_CMD_STRING))
		return (syntax_error(e, ERR_COMMENT_H, NULL, head->next->line));
	if (ptr2->next)
	{
		printf("%s\n", ptr2->next->lab);
		if (!ptr2->next->lab)
			return (syntax_error(e, ERR_COMNOTF, NULL, head->next->line));
		if (ptr2->next->lab && ft_strlen(ptr2->next->lab) > 2048)
			return (syntax_error(e, ERR_COMMENT_LEN, NULL, head->next->line));
	}
	else
		return (syntax_error(e, ERR_COMMENT_H, NULL, head->next->line));
	return (0);
}
