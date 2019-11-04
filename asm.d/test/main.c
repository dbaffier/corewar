/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:47:36 by mmonier           #+#    #+#             */
/*   Updated: 2019/11/04 23:01:47 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	init_screen(t_print *print)
{
	initscr();
	clear();
	refresh();
	cbreak();
	noecho();
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	print->win = newwin(0, 0, 0, 0);
	keypad(print->win, TRUE);
}

int		main(int ac, char **av)
{
	t_print	print;

	ft_memset(&print, 0, sizeof(t_print));
	//init_screen(&print);
	print.fd = open(av[1], O_RDONLY);
	visuprint(&print);
	close(print.fd);
	//endwin();
	return (0);
}
