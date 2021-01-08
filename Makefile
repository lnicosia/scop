# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/01 15:56:21 by lnicosia          #+#    #+#              #
#    Updated: 2020/03/06 14:17:34 by lnicosia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

MAKEFILE = Makefile

LIB_DIR = lib
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .
INCLUDES_DIR = includes
LIBFT_DIR = libft
INSTALL_DIR = install
GLAD_DIR = glad
SED = sed
ROOT = sudo
OPENGL = /usr/include/GLFW/glfw3.h

LIBFT = $(LIBFT_DIR)/libft.a
GLAD = $(GLAD_DIR)/glad.a

LIB_RAW = 

SRC_RAW = main.c scop.c init_opengl.c ../glad/src/glad.c

HEADERS = scop.h

#
# Creation of files path
#

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

RESOURCES =

OPTI_FLAGS = -O3
GLFW_FLAGS = $(pkg-config --cflags glfw3 gl) $(pkg-config --libs glfw3 gl)

CFLAGS =	-Wall -Wextra -Werror -I $(INCLUDES_DIR) \
	  	-I $(LIBFT_DIR) -I $(GLAD_DIR)/include \
		#$(OPTI_FLAGS) \
		#-fsanitize=address -g3 \
	
#
# Setting right flags and files dependencies to link external libs
# according to user's os
#

ifeq ($(OS), Windows_NT)
else
	UNAME_S = $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
		OPTI_FLAGS += -flto
		SED = gsed
    else
		CFLAGS += -Wno-misleading-indentation
		OPTI_FLAGS += -flto
    endif
endif

#
# Color declarations
#

RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"

#
# Rules
#

all: $(OPENGL) $(NAME)
	@printf $(CYAN)"[INFO] Buidling libft..\n"$(RESET) 
	@make --no-print-directory -C $(LIBFT_DIR)
	@printf $(RESET)
	@printf $(CYAN)"[INFO] Buidling scop..\n"$(RESET) 

$(OPENGL) = sudo apt-get install libglfw3-dev

$(LIBFT):
	@make -C $(LIBFT_DIR) -j8

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@ $(CFLAGS) 

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) 
	@printf $(CYAN)"[INFO] Linking ${BIN_DIR}/${NAME}\n"$(RESET)
	gcc $(CFLAGS) $(GLFW_FLAGS) $(OBJ) $(LIBFT) -o $(NAME) 
	@printf ${GREEN}"[INFO] Compiled $(BIN_DIR)/$(NAME) with success!\n"
	@printf ${RESET}

clean:
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	@make clean -C libft
	rm -rf $(OBJ_DIR)

fclean:
	@make fclean -C libft
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	rm -rf $(OBJ_DIR)
	@printf ${CYAN}"[INFO] Removing $(BIN_DIR)/$(NAME)"

re: fclean all

.PHONY: fclean all clean libft
