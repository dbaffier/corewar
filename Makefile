# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/18 16:01:33 by bmellon           #+#    #+#              #
#    Updated: 2019/09/19 23:16:34 by gbourgeo         ###   ########.fr        #
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

DEP_DIR		= .deps/
DEP			= $(addprefix $(DEP_DIR), $(SRC:.c=.d))

all: $(DEP_DIR) $(OBJS_DIR) lib $(NAME)

$(DEP_DIR):
	@mkdir -p $@

$(OBJS_DIR):
	@mkdir -p $@

lib:
	@make -C $(LFT_PATH)

$(NAME): $(OBJS_VM)
	@$(CC) -o $@ $^ $(LFT_LINK)
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
	@make -C $(LFT_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LFT_PATH) fclean

re: fclean all

.PHONY: clean fclean all re
