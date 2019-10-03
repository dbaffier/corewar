/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:49:40 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/03 17:04:16 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

int	asm_comment(t_aolist *head, char **line)
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
	strncpy(str, tmp, len);
	free(*line);
	*line = str;
	return (0);
}
