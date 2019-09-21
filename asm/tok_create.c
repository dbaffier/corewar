/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:00:21 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/21 22:10:58 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

int		create_token(t_token **head, char *line, size_t st, size_t *i)
{
	if (grep_opcode(head, line, st, i) > 0)
		return (ERR_MALLOC);
	if (grep_arg(*head, line, i) > 0)
		return (ERR_MALLOC);
	return (0);
}

int		tokenize(t_token **head, char *line, size_t *i)
{
	size_t	st;
	size_t	len;

	len = 0;
	st = *i;
	if (line[*i] == '.')
		return (create_dot(head, line, i));
	if (is_label(line, *i))
		return (create_label(head, line, i));
	return (create_token(head, line, st, i));
}

static int	grep_comment(t_aolist *head, char **line)
{
	char	*str;
	char	*new;
	char	*tmp;
	size_t	i;
	size_t	len;

	new = ft_strchr(*line, COMMENT_CHAR);
	len = new - *line;
	new = malloc(sizeof(char) * ft_strlen(new) + 1);
	i = 0;
	str = *line;
	while (str[len + i])
	{
		new[i] = str[len + i];
		i++;
	}
	new[i] = '\0';
	head->comment = new;
	str = malloc(sizeof(char) * len + 1);
	i = 0;
	tmp = *line;
	while (i < len)
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = '\0';
	free(*line);
	*line = str;
	return (0);
}

int		tok_create(t_aolist *head, char **line)
{
	t_token		*tok;
	char		*dup;
	size_t		i;

	i = 0;
	tok = NULL;
	if (ft_strchr(*line, COMMENT_CHAR))
		if (grep_comment(head, line) > 0)
			return (ERR_MALLOC);
	dup = *line;
	while (dup[i])
	{
		if (dup[i] == ' ' || dup[i] == '\t')
			i++;
		else if (dup[i])
		{
			if (tokenize(&tok, dup, &i) > 0)
				return (ERR_MALLOC);
		}
	}
	head->tok = tok;
	return (0);
}
