/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 01:48:11 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/18 03:16:09 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static int token_lst(t_env *e)
{
	int			ret;
	t_token		*tok;
	char		*line;

	ret = 0;
	line = NULL;
	while ((ret = get_next_line(e->fd, &line)) > 0)
	{
		tok_create(&tok);

		free(line);
	}
	
}

int		parser(t_env *e, char *file)
{
	int		ret;

	if ((ret = asm_file_open(e, file)) > 1)
		return (ret);
	if ((ret = token_lst(e)) > 1)
		return (1);
}
