/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcurrent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:10:13 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/07 16:58:28 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static char		*readtype(int idx, int *param)
{
	if (param[idx] == E_REG)
		return ("REGISTER");
	if (param[idx] == E_DIR)
		return ("DIRECT");
	return ("INDIRECT");
}
static void		printtype(t_print *print, t_val *val)
{
	if (print->pos == 1)
		return ;
	if (val->type == E_MAGIC)
		ft_printf("This is the magic number ");
	else if (val->type == E_NAME)
		ft_printf("Writting name ");
	else if (val->type == E_PAD)
		ft_printf("Writting padding ");
	else if (val->type == E_SIZE)
		ft_printf("writting size ");
	else if (val->type == E_COMMENT)
		ft_printf("Writting comment ");
	else if (val->type == E_OPCODE)
		ft_printf("Writting opcode ");
	else if (val->type == E_EBYTE && val->ebyte == 1)
		ft_printf("Writting encoding byte ");
	else if (val->type == E_INSTRUC && val->ebyte == 1) 
		ft_printf("Writting %d instruction type %s ", 
				print->idx, readtype(print->idx, print->param));
	else if (val->type == E_INSTRUC && val->ebyte == 0) 
		ft_printf("Writting instructiom type DIRECT ");
}

void			printcurrent(t_print *print, unsigned char buff)
{
	static int	x = 2;
	static int	y = 2;
	char		sep;
	WINDOW		*hexwin;

	hexwin = subwin(print->win, y + 2, 53, 1, 1);
	sep = 0;
	if (x > 50)
	{
		x = 2;
		y++;
	}
	box(hexwin, 0, 0);
    touchwin(hexwin);
	prefresh(hexwin, y + 2, 53, 1, 1, 0, 0);
	mvwprintw(print->win, y, x, "%x", buff);
	wrefresh(print->win);
	wclear(hexwin);
	//printtype(print, print->val);
	if (x == 22)
		x += 3;
	x += 3;
}
