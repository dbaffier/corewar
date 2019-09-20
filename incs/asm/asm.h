/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:19:41 by dbaffier          #+#    #+#             */
/*   Updated: 2019/09/20 03:33:11 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define OK		0
# define NOT_OK	1

# include "op.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define ERR_FILE			1
# define ERR_EXTENSION		2
# define ERR_NOFILE			3
# define ERR_OVERFLOW		4
# define ERR_OPEN			5
# define ERR_MALLOC			6

# define ERR_STR_FILE		"filename too short"
# define ERR_STR_EXTENSION	"file extension is not correct"
# define ERR_STR_NOFILE		"no given file"
# define ERR_STR_OVERFLOW	"too much argument given"

enum {
	LABEL = 0,
	OP_CODE,
	PARAM,
	DOT,
	DIRECT,
	UNDIRECT,
	REGISTER,
};

typedef struct		s_token
{
	char				*val;
	int					type;
	struct s_token		*next;
}					t_token;

typedef struct		s_aolist
{
	t_token				*tok;
	char				*comment;
	struct s_aolist		*next;
}					t_aolist;

typedef struct		s_env
{
	t_aolist	*aolist;
	int			fd;
}					t_env;

int			asm_file_open(t_env *e, char *file);
int			asm_file(int ac, char **av);

char		*str_s_e(char *line, int s, int e);
int			create_label(t_token **head, char *val, size_t *i);
int			create_dot(t_token **head, char *val, size_t *i);
int			grep_opcode(t_token **head, char *line, size_t st, size_t *i);
int			is_label(char *line, int start);
int			tok_create(t_aolist *head, char *line);
int			parser(t_env *e, char *file);
void		ft_freetab(char ***table);
void		push_front(void *head, void *new, int type);

#endif
