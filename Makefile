# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 16:01:33 by bmellon           #+#    #+#              #
#    Updated: 2019/09/18 23:33:01 by gbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= corewar

CC			= gcc 
CFLAGS		= -Wall -Werror -Wextra
CFLAGS		+= -std=c11 -Wmissing-prototypes -pedantic -pedantic-errors

INCS		= -I$(LFT_PATH)/inc -I$(VM_INC_D)

OBJS_DIR	= $(VM_DIR)objs/

LFT_PATH	= libft/
LFT_LIB		= $(LFT_PATH)libft.a
LFT_LINK	= -L$(LFT_PATH) -lft

OBJS_VM		+= $(addprefix $(OBJS_DIR), $(SRCS_VM:.c=.o))

VM_DIR		=	vm/
VM_SRC_D	= $(VM_DIR)srcs/
VM_INC_D	= $(VM_DIR)incs
SRCS_VM		+=	args.c		\
				champ.c		\
				main.c		\
				op.c		\
				errors.c	\
				arena.c		\

RED			= \x1b[1;31m
GREEN		= \x1b[1;32m
RESET		= \x1b[0m

all: $(OBJS_DIR) lib $(NAME)

$(OBJS_DIR):
	@mkdir -p $@

lib:
	@make -C $(LFT_PATH)

$(NAME): $(OBJS_VM)
	@$(CC) -o $@ $^ $(LFT_LINK)
	@echo "RELEASE THE $(RED) C O R E W A R $(RESET)"

$(OBJS_DIR)%.o: $(VM_SRC_D)%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS)

clean:
	@$(RM) -rf $(OBJS_DIR)
	@make -C $(LFT_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LFT_PATH) fclean

re: fclean all

.PHONY: clean fclean all re
