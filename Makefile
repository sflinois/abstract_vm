# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/07 10:40:24 by sflinois          #+#    #+#              #
#    Updated: 2019/06/01 13:54:39 by sflinois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstract_vm

SRC_PATH = ./srcs
SRC_NAME = main.cpp OperandFactory.cpp Operand.cpp Vm.cpp LexerParser.cpp
OBJ_PATH = objs
INC = -I./includes

CC = clang++
CC_FLAGS = -Wall -Werror -Wextra -std=c++11

OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) -o $@ $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
		@mkdir $(OBJ_PATH) 2>/dev/null || true
		@$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<

clean:
		@rm -fv $(OBJ)
		@rmdir $(OBJ_PATH) 2>/dev/null || true

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
