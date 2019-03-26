# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 13:22:53 by rkulahin          #+#    #+#              #
#    Updated: 2019/03/26 15:21:11 by rkulahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
NAME2 = asm
LIB = libftprintf.a

OBJ_VM_DIR	= ./obj_vm/
OBJ_ASM_DIR	= ./obj_asm/
SRC_VM_DIR = ./vm/
SRC_ASM_DIR = ./assembler/

SRC_VM = main.c \
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
SRC_ASM = check_execution.c \
		convert.c \
		convert_helper.c \
		detect_helper.c \
		detect_type.c \
		error_open.c \
		init_lbl_cmd.c \
		instructions.c \
		main.c \
		match_labels.c \
		op.c \
		read_file.c \
		read_lbl_cmd.c \
		utils2.c \
		valid.c

OBJ_VM = $(addprefix $(OBJ_VM_DIR), $(SRC_VM:.c=.o))
OBJ_ASM = $(addprefix $(OBJ_ASM_DIR), $(SRC_ASM:.c=.o))

INCL = -I includes/
FLAGS =	-g -Wall -Wextra -Werror

all: $(NAME) $(NAME2)
$(NAME):	$(OBJ_VM) $(LIB)
	gcc -o $(NAME) $(FLAGS) -lncurses $(OBJ_VM) $(LIB)

$(OBJ_VM):		| $(OBJ_VM_DIR)

$(OBJ_VM_DIR):
		@mkdir $(OBJ_VM_DIR)

$(OBJ_VM_DIR)%.o:	$(SRC_VM_DIR)%.c
		@gcc -c $< -o $@ $(FLAGS) $(INCL)

$(NAME2):	$(OBJ_ASM) $(LIB)
	gcc -o $(NAME2) $(FLAGS) -lncurses $(OBJ_ASM) $(LIB)

$(OBJ_ASM):		| $(OBJ_ASM_DIR)

$(OBJ_ASM_DIR):
		@mkdir $(OBJ_ASM_DIR)

$(OBJ_ASM_DIR)%.o:	$(SRC_ASM_DIR)%.c
		@gcc -c $< -o $@ $(FLAGS) $(INCL)

$(LIB):
	$(MAKE) all -f ./libftprintf/Makefile
clean :
	@rm -rf $(OBJ_VM_DIR)
	@rm -rf $(OBJ_ASM_DIR)
	$(MAKE) clean -f ./libftprintf/Makefile
fclean : clean
	@rm -f $(NAME)
	@rm -f $(NAME2)
	$(MAKE) fclean -f ./libftprintf/Makefile
re : fclean all
