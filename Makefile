# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 16:01:33 by bmellon           #+#    #+#              #
#    Updated: 2019/10/24 21:31:39 by dbaffier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR	= vm.d/
ASM		= asm.d/

LIBFT	= libft/

all:
	make -C $(LIBFT)
	make -C $(ASM)
	make -C $(COREWAR)

clean:
	make -C $(LIBFT) clean
	make -C $(ASM) clean
	make -C $(COREWAR) clean

fclean: clean
	make -C $(LIBFT) fclean
	make -C $(ASM) fclean
	make -C $(COREWAR) fclean

re: fclean all
