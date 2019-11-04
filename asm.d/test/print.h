/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:48:46 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/04 22:57:46 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "libft.h"
# include "ft_printf.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <curses.h>
# include <stdio.h>

enum	e_type
{
	E_MAGIC,
	E_NAME,
	E_PAD,
	E_SIZE,
	E_COMMENT,
	E_OPCODE,
	E_EBYTE,
	E_INSTRUC,
};

enum	e_param
{
	E_NONE,
	E_REG,
	E_DIR,
	E_IND,
};

typedef struct	s_print
{
	WINDOW			*win;
	int				fd;
	int				param[3];
	int				idx;
	int				ninstruc;
	int				pos;
	struct	s_val	*val;
}				t_print;

typedef struct	s_val
{
	int		type;
	int		size;
	int		ebyte;
}				t_val;

void	decode(t_print *print, unsigned int buff);
void	visuprint(t_print *print);
void	printcurrent(t_print *print, unsigned char buff);
void	rendersyntax(t_print *print, t_val *val, unsigned char buff);

#endif
