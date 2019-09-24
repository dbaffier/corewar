/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 01:20:28 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/24 01:43:08 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

int		syntax_error(t_env *e, int error, t_token *tok, int line)
{
	static char		*tab[] = { NULL,  ERR_STR_NAME, ERR_STR_NAME_LEN,
		ERR_STR_COMMENT, ERR_STR_COMMENT_LEN};

	if (error < 5)
		ft_printf("%s\n", tab[error]);
	else
	{
		if (error == ERR_ARG_N)
			ft_dprintf(2, "too much arguments on line [%d]\n", line);
		else if (tok->type == LABEL)
			ft_dprintf(2, "lexical error on label [%s] on line [%d]\n", tok->lab, line);
		else if (tok->type == OP_CODE)
			ft_dprintf(2, "lexical error on [%s] on line [%d]\n", tok->lab, line);
		else if (error == ERR_LAB)
		{
			ft_dprintf(2, "lexical error at [TOKEN][%s] on line [%d]\n", tok->lab, line);
			ft_dprintf(2, "authorized char : \"abcdefghijklmnopqrstuvwxyz_0123456789\"\n");
		}
		else if (error == ERR_LAB_FOUND)
			ft_dprintf(2, "lexical error at [TOKEN][%s] on line [%d] was not found \n", tok->lab, line);
		else
			ft_printf("Error\n");
	}
	(void)e;
	exit(1);
}
