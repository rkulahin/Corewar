# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seshevch <seshevch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 13:22:53 by rkulahin          #+#    #+#              #
#    Updated: 2019/03/22 12:54:30 by seshevch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
LIB = libftprintf.a

OBJ_DIR	= ./obj_vm/
SRC_DIR = ./vm/

SRC = main.c \
		bonus_parce.c \
		parce.c \
		valid.c \
		vm_map.c \
		func.c \
		op.c \
		corewar.c \
		other.c \
		op_live.c \
		op_st.c \
		op_add.c \
		op_sub.c \
		op_fork.c \
		op_and.c \
		op_or.c \
		op_xor.c \
		op_sti.c \
		op_load_index.c \
		op_load.c \
		op_long_load_index.c \
		op_long_load.c \
		op_zjmp.c \
		op_aff.c  \
		parce_plus.c \
		print_log4.c \
		curses.c \
		curses2.c  \
		corewar2.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INCL = -I includes/
FLAGS =	-g -Wall -Wextra -Werror -O3

all: $(NAME)
$(NAME):	$(OBJ) $(LIB)
	gcc -o $(NAME) $(FLAGS) -lncurses $(OBJ) $(LIB)

$(OBJ):		| $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@gcc -c $< -o $@ $(FLAGS) $(INCL)

$(LIB):
	$(MAKE) all -f ./libftprintf/Makefile
clean :
	@rm -rf $(OBJ_DIR)
	$(MAKE) clean -f ./libftprintf/Makefile
fclean : clean
	@rm -f $(NAME)	
	$(MAKE) fclean -f ./libftprintf/Makefile
re : fclean all
