# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aorji <aorji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 14:57:32 by aorji             #+#    #+#              #
#    Updated: 2019/08/19 15:38:32 by aorji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ssl

OBJ_DIR =   ./obj/
SRC_DIR =   ./src/
INC_DIR =	./inc/
LIB_DIR	=	./lib/

CC      =	gcc
FLAGS   =   -Wall -Wextra -Werror --debug

SRC     =   main.c															\
			input_validator.c file_validation.c								\
			message_processing.c flags_processing.c structure_processing.c	\
			md5.c		md5_output.c output.c										\
			sha256.c	sha256_output.c										\
			sha224.c	sha224_output.c\
			sha384.c sha384_output.c
OBJ     =   $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC		=	$(INC_DIR)
PRNTF	=	libft-ft_printf/libftprintf.a

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)	$(PRNTF) -I $(INC)
	echo "\033[32m[ ✔ ] "$(NAME) created" \033[0m"

$(OBJ): $(LIB_DIR) $(OBJ_DIR)

$(LIB_DIR):
	mkdir $(LIB_DIR)
	make -C ./libft-ft_printf && cp $(PRNTF) $(LIB_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	# -c == Compile the source files, but do not link ==> .o
	$(CC) $(FLAGS) $< -c -o $@ 

re:
	make fclean
	make

clean:
	make clean -C ./libft-ft_printf
	rm -f $(OBJ)
	echo "\033[31m[ × ] "$(OBJ) removed" \033[0m"

fclean: clean
	make fclean -C ./libft-ft_printf
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)
	echo "\033[31m[ × ] "$(NAME) and $(PRNTF) removed" \033[0m"
