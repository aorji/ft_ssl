# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aorji <aorji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 14:57:32 by aorji             #+#    #+#              #
#    Updated: 2019/08/21 15:08:01 by aorji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#g++ src_cpp/UnitTest.cpp src_cpp/main.cpp src_cpp/InitTestCases.cpp inc_hpp/UnitTest.hpp  -std=c++11 && ./a.out#
NAME	=	ft_testssl

OBJ_DIR =   ./obj/
SRC_DIR =   ./src_cpp/
INC_DIR =	./inc_hpp/

CC      =	g++
FLAGS   =   -Wall -Wextra -Werror --debug

SRC     =   main.cpp InitTestCases.cpp UnitTest.cpp
OBJ     =   $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
INC		=	$(INC_DIR)

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -I $(INC)
	echo "\033[32m[ ✔ ] "$(NAME) created" \033[0m"

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	# -c == Compile the source files, but do not link ==> .o
	$(CC) -c $< -o $@ $(FLAGS) -std=c++11

re:
	make fclean
	make

clean:
	rm -f $(OBJ)
	echo "\033[31m[ × ] "$(OBJ) removed" \033[0m"

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	echo "\033[31m[ × ] "$(NAME) removed" \033[0m"
