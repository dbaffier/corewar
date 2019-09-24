/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_syntax_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:36:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/24 02:38:18 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

int		asm_syntax_arg(t_env *e, t_aolist *head, t_token *curr)
{
	int		mn[3];
	int		i;

	ft_memset(&mn, 0, sizeof(mn));
	if (curr->arg_n > 3)
		return (syntax_error(e, ERR_ARG_N, curr, head->line));
	i = 0;
	while (curr)
	{
		if (g_op_tab[head->id].types[i] & curr->type)
			printf("Found similar types\n");
		if (curr->type & T_REG)
			mn[i++] = T_REG;
		else if (curr->type & T_DIR)
			mn[i++] = T_DIR;
		else
			mn[i++] = T_IND;
		curr = curr->next;
	}
	return (0);
}
