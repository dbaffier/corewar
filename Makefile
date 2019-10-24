# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmellon <bmellon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 16:01:33 by bmellon           #+#    #+#              #
#    Updated: 2019/10/24 22:15:03 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM		= vm.d/
ASM		= asm.d/

all: vm asm

vm:
	make -C $(VM)

asm:
	make -C $(ASM)

clean:
	make -C $(VM) clean
	make -C $(ASM) clean

fclean: clean
	make -C $(VM) fclean
	make -C $(ASM) fclean

re: fclean all
