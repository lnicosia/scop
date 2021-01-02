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
SED = sed
ROOT = sudo
OPEN_GL = temp

LIBFT = $(LIBFT_DIR)/libft.a

LIB_RAW = 

SRC_RAW = main.c

HEADERS = 

#
# Creation of files path
#

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

RESOURCES =

OPTI_FLAGS = -O3

CFLAGS =	-Wall -Wextra -Werror -I $(INCLUDES_DIR) \
	  	-I $(LIBFT_DIR) \
		$(OPTI_FLAGS) \
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

all:
	@printf $(CYAN)"[INFO] Buidling libft..\n"$(RESET) 
	@make --no-print-directory -C $(LIBFT_DIR)
	@printf $(RESET)
	@printf $(CYAN)"[INFO] Buidling scop..\n"$(RESET) 
	@make --no-print-directory $(EDITOR_DIR)/$(EDITOR_NAME)

$(NAME): all

$(OPEN_GL) = sudo apt-get install freeglut3-dev

$(LIBFT):
	@make -C $(LIBFT_DIR) -j8

$(OBJ_GAME_DIR):
	@mkdir -p $(OBJ_GAME_DIR)

$(OBJ_EDITOR_DIR):
	@mkdir -p $(OBJ_EDITOR_DIR)

$(OBJ_ALL_DIR):
	@mkdir -p $(OBJ_ALL_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@ $(CFLAGS) 

$(GAME_NAME): $(LIBFT) $(OBJ_DIR) 
	@printf $(CYAN)"[INFO] Linking ${GAME_DIR}/${GAME_NAME}\n"$(RESET)
	@gcc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) 
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
