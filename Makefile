# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 16:01:33 by bmellon           #+#    #+#              #
#    Updated: 2019/09/23 01:30:48 by bmellon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR	= vm/

LIBFT	= libft/

all:
	make -C $(LIBFT)
	make -C $(COREWAR)

clean:
	make -C $(LIBFT) clean
	make -C $(COREWAR) clean

fclean: clean
	make -C $(LIBFT) fclean
	make -C $(COREWAR) fclean

re: fclean all
