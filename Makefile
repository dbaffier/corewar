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

NAME		= corewar

VM_DIR		= vm/
VM_SRC_D	= $(VM_DIR)srcs/
VM_INC_D	= $(VM_DIR)incs/
VM_SRC		+=	get_args.c			\
				get_player.c		\
				main.c				\
				op.c				\
				errors.c			\
				arena.c				\
				game.c				\
				operation_tools.c	\
				operations1_5.c		\
				operations6_10.c	\
				operations11_15.c	\
				operations_aff.c	\

CC			= gcc 
CFLAGS		= -Wall -Werror -Wextra
CFLAGS		+= -std=c11 -Wmissing-prototypes -pedantic -pedantic-errors

INCS		= -I$(LFT_DIR)inc -I$(VM_INC_D)
LIBS		= -L$(LFT_DIR) -lft

OBJS_DIR	= $(VM_DIR)objs/
OBJS_VM		+= $(addprefix $(OBJS_DIR), $(VM_SRC:.c=.o))

DEP_DIR		= .deps/
DEP			= $(addprefix $(DEP_DIR), $(SRC:.c=.d))

LFT_DIR		= libft/

RED			= \x1b[1;31m
GREEN		= \x1b[1;32m
RESET		= \x1b[0m

all: $(DEP_DIR) $(OBJS_DIR) lib $(NAME)

$(DEP_DIR):
	@mkdir -p $@

$(OBJS_DIR):
	@mkdir -p $@

lib:
	@make -C $(LFT_DIR)

$(NAME): $(OBJS_VM)
	$(CC) -o $@ $^ $(LIBS)
	@echo "RELEASE THE $(RED) C O R E W A R $(RESET)"

$(OBJS_DIR)%.o: $(VM_SRC_D)%.c
$(OBJS_DIR)%.o: $(VM_SRC_D)%.c $(DEP_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEP_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEP_DIR)$*.Td $(DEP_DIR)$*.d && touch $@

$(DEP_DIR)%.d: ;
.PRECIOUS: $@

-include $(DEP)

clean:
	@$(RM) -rf $(OBJS_DIR)
	@$(RM) -rf $(DEP_DIR)
	@make -C $(LFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LFT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re
