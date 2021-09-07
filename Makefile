# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/01 15:56:21 by lnicosia          #+#    #+#              #
#    Updated: 2021/09/07 14:43:53 by lnicosia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

MAKEFILE = Makefile

LIB_DIR = lib
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .
INCLUDES_DIR = includes
LIBFT_DIR = $(LIB_DIR)/libft
LIBMFT_DIR = $(LIB_DIR)/libmft
BMP_PARSER_DIR = $(LIB_DIR)/bmp_parser
INSTALL_DIR = install
GLAD_DIR = $(LIB_DIR)/glad
SED = sed
ROOT = sudo
TARGET = unix
OPENGL = /usr/include/GLFW/glfw3.h

#LIBS
LIBFT = $(LIBFT_DIR)/libft.a
LIBMFT = $(LIBMFT_DIR)/libmft.a
BMP_PARSER = $(BMP_PARSER_DIR)/bmp_parser.a
GLAD = $(GLAD_DIR)/libglad.a
GLFW = -ldl -lm

LDLIBS = $(LIBMFT) $(BMP_PARSER) $(GLAD) $(GLFW) $(LIBFT)

LDFLAGS = -L $(LIBFT_DIR) -L $(LIBMFT_DIR) -L $(BMP_PARSER_DIR)

LIB_RAW = 

SRC_RAW =	main.c scop.c init_opengl.c ft_fatal_error.c \
			free_all.c viewport_update_callback.c key_callback.c \
			draw_triangle.c shader.c object.c object_transformation.c \
			projection_matrix.c parse_object.c inputs.c glad.c 

HEADERS = scop.h env.h inputs.h shader.h object.h camera.h obj_parser.h

#
# Creation of files path
#

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

RESOURCES =

OPTI_FLAGS = -O3

CFLAGS =	-Wall -Wextra -Werror -Wpadded -Wconversion -I $(INCLUDES_DIR) \
	  	-I $(LIBFT_DIR)/includes -I $(BMP_PARSER_DIR)/includes \
		-I $(LIBMFT_DIR)/includes -I $(GLAD_DIR)/include -fsanitize=address -g3 \
		#$(OPTI_FLAGS) \
		\
		
	
#
# Setting right flags and files dependencies to link external libs
# according to user's os
#

ifeq ($(OS), Windows_NT)
	GLFW += lib/glfw3.dll
	CFLAGS += -Wno-misleading-indentation
else
	UNAME_S = $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
	OPTI_FLAGS += -flto
	SED = gsed
    else
	CFLAGS += -Wno-misleading-indentation
	GLFW += -lglfw
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

all: $(OPENGL)
	@printf $(CYAN)"[INFO] Building libft..\n"$(RESET)
	@make -j4 --no-print-directory -C $(LIBFT_DIR)
	@printf $(CYAN)"[INFO] Building libmft..\n"$(RESET)
	@make -j4 --no-print-directory -C $(LIBMFT_DIR)
	@printf $(CYAN)"[INFO] Building bmp_parser..\n"$(RESET)
	@make -j4 --no-print-directory -C $(BMP_PARSER_DIR)
	@printf $(CYAN)"[INFO] Building scop..\n"$(RESET)
	@make -j4 --no-print-directory $(BIN_DIR)/$(NAME)

$(OPENGL):
	sudo apt-get update
	sudo apt-get install libglfw3-dev

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(LIBMFT):
	@make --no-print-directory -C $(LIBMFT_DIR)

$(BMP_PARSER):
	@make --no-print-directory -C $(BMP_PARSER_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@ $(CFLAGS) 

$(NAME): $(LIBFT) $(LIBMFT) $(BMP_PARSER) $(OBJ_DIR) $(OBJ) 
	@printf $(CYAN)"[INFO] Linking ${BIN_DIR}/${NAME}\n"$(RESET)
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)
	@printf ${GREEN}"[INFO] Compiled $(BIN_DIR)/$(NAME) with success!\n"
	@printf ${RESET}

clean:
	@make --no-print-directory clean -C $(LIBFT_DIR)
	@make --no-print-directory clean -C $(LIBMFT_DIR)
	@make --no-print-directory clean -C $(BMP_PARSER_DIR)
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	rm -rf $(OBJ_DIR)

fclean:
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@make --no-print-directory fclean -C $(LIBMFT_DIR)
	@make --no-print-directory fclean -C $(BMP_PARSER_DIR)
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	rm -rf $(OBJ_DIR)
	@printf ${CYAN}"[INFO] Removing $(BIN_DIR)/$(NAME)\n"$(RESET)
	rm -rf $(BIN_DIR)/$(NAME)

re: fclean all

.PHONY: fclean all clean libft
