# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/13 17:52:39 by rkulahin          #+#    #+#              #
#    Updated: 2019/01/04 11:32:37 by rkulahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_DIR = ./libftprintf/srcs/
LIB_DIR = ./libftprintf/libft/
OBJ_DIR	= ./libftprintf/obj/

LIB = 	ft_atoi.c \
		ft_btree_create_node.c \
		ft_bzero.c \
		ft_cnumbers.c \
		ft_cwords.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_islower.c \
		ft_isprint.c \
		ft_isupper.c \
		ft_itoa.c \
		ft_lenword.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		ft_pow.c
SRC = 	find.c \
		ft__valid.c \
		ft_arg.c \
		ft_c.c \
		ft_itoa_base.c \
		ft_itoa_base_u.c \
		ft_printf.c \
		ft_s.c \
		ft_x.c \
		ft_x_mod.c \
		ft_xx.c \
		ft_xx_mod.c \
		ft_p.c \
		ft_i.c \
		ft_i_mod.c \
		ft_u.c \
		ft_u_mod.c \
		ft_o.c \
		ft_o_mod.c

OBJ =	$(addprefix $(OBJ_DIR), $(LIB:.c=.o))\
		$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INCL = -I includes/
FLAGS = -Wall -Wextra -Werror -g

all:		$(NAME)

$(NAME):	$(OBJ)
	@ar rc $(NAME) $(OBJ)

$(OBJ):		| $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(LIB_DIR)%.c
		@gcc -c $< -o $@ $(FLAGS) $(INCL)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@gcc -c $< -o $@ $(FLAGS) $(INCL)
clean :
	@rm -rf $(OBJ_DIR)
fclean : clean
	@rm -f $(NAME)	
re : fclean all
