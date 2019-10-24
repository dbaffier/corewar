# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/26 23:23:36 by dbaffier          #+#    #+#              #
#    Updated: 2019/10/24 21:31:55 by dbaffier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../asm

CC = gcc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -std=c11 -Wmissing-prototypes -pedantic -pedantic-errors

LIBFT_PATH = ../libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a
LIBFT_LINK = -L$(LIBFT_PATH) -lft -lncurses

INC_DIR = incs/
INCS = -I$(LIBFT_PATH)/inc -I$(INC_DIR)

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS_DIR = .deps/
DEPS = $(addprefix $(DEPS_DIR), $(SRCS:.c=.d))

RM = /bin/rm -rf

SRCS_DIR = asm_dir/

CONV_DIR = conversion/
SRCS +=	binary.c				\
		create_corfile.c		\
		cw_hexdump.c			\
		way_to_corewar.c		\
		user_file.c				\
		cut_path.c				\

PARSE_DIR = parsing/
SRCS += asm_aolist.c			\
		asm_arg.c				\
		asm_comment.c			\
		asm_dot.c				\
		asm_file.c				\
		asm_parse.c				\
		asm_size.c				\
		asm_syntax_arg.c		\
		asm_syntax_error.c		\
		asm_syntax_header.c		\
		asm_syntax_label.c		\
		asm_syntax_op.c			\
		asm_grep_opc.c			\
		asm_lab_create.c		\
		asm_op.c				\
		asm_splitws.c			\
		asm_tok.c				\
		asm_tools.c				\
		asm_free.c				\
		main.c					\
		parse_flag.c			\
		syntax_analysis.c		\

PRINT_DIR = print/
SRCS += buffer_functions.c		\
		handle_colors.c			\
		handle_zero.c			\
		init_screen.c			\
		print_end.c				\
		print_header.c			\
		print_hex.c				\
		print_offset.c			\
		print_path.c			\
		print_tools.c			\
		asm_helper.c			\
		parse_narg.c			\

WRITING_DIR = writing/
SRCS += write_header.c			\
		write_magic.c			\
		write_opc.c				\
		write_param.c			\
		write_type.c			\

DEASM_DIR = deasm/
SRCS += deasm.c					\
		deasm_file.c			\
		dswrite_instructions.c	\
		dswrite_opc.c			\
		print.c					\

all: $(OBJS_DIR) $(DEPS_DIR) $(LIBFT_LIB) $(NAME)

$(OBJS_DIR):
	@mkdir -p $@

$(DEPS_DIR):
	@mkdir -p $@

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LIBFT_LINK)

$(OBJS_DIR)%.o: $(SRCS_DIR)$(CONV_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(CONV_DIR)%.c $(DEPS_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(PARSE_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(PARSE_DIR)%.c $(DEPS_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(PRINT_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(PRINT_DIR)%.c $(DEPS_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(WRITING_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(WRITING_DIR)%.c $(DEPS_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(OBJS_DIR)%.o: $(SRCS_DIR)$(DEASM_DIR)%.c
$(OBJS_DIR)%.o: $(SRCS_DIR)$(DEASM_DIR)%.c $(DEPS_DIR)%.d
	$(CC) -MT $@ -MMD -MP -MF $(DEPS_DIR)$*.Td $(CFLAGS) -o $@ -c $< $(INCS)
	@mv -f $(DEPS_DIR)$*.Td $(DEPS_DIR)$*.d && touch $@

$(DEPS_DIR)%.d: ;
.PRECIOUS: $@

-include $(DEPS)

re: fclean all

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(DEPS_DIR)
	@$(RM) $(OBJS_DIR)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)
