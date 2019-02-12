# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 10:40:24 by sflinois          #+#    #+#              #
#    Updated: 2019/02/12 13:49:58 by sflinois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstract_vm

SRC_PATH = ./srcs
SRC_NAME = main.cpp OperandFactory.cpp Operand.cpp Vm.cpp
OBJ_PATH = objs

CC = clang++
CC_FLAGS = -Wall -Werror -Wextra -Wno-c++11-extensions

OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) -o $@ $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
		@mkdir $(OBJ_PATH) 2>/dev/null || true
		@$(CC) $(CC_FLAGS) -o $@ -c $<

clean:
		@rm -fv $(OBJ)
		@rmdir $(OBJ_PATH) 2>/dev/null || true

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
