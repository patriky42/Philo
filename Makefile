# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 12:15:51 by pabastid          #+#    #+#              #
#    Updated: 2024/02/22 11:18:59 by pabastid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
SRC := errors.c data.c time_control.c free_and_destroy.c \
				printing.c create.c check_and_control_all.c routine.c main.c 
SRC_DIR := src/
BUILD_DIR := .build/
# OBJ := $(SRC:.c=.o)
# DEP := $(SRC:.c=.d)
OBJ := $(addprefix $(BUILD_DIR), $(SRC:.c=.o))
DEP := $(addprefix $(BUILD_DIR), $(SRC:.c=.d))
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g -MMD -pthread -fsanitize=thread
RM := rm -rf
LIBS := -lpthread
HEADER := inc/
INCLUDE := -I $(HEADER)

###################
#COLORS

COLOR_RESET = \033[0m
COLOR_BOLD = \033[1m
COLOR_UNDERLINE = \033[4m
COLOR_RED = \033[31m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m
COLOR_BLUE = \033[34m
COLOR_MAGENTA = \033[35m
COLOR_CYAN = \033[36m

###################


$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(OBJ) $(NAME)

$(LIBS):
	@$(MAKE) -C libftprintf

$(NAME): $(LIBS) $(OBJ)
	@$(CC) $(CFLAGS) $(LIBPATH) $(OBJ) -o $(NAME)
	@echo "$(COLOR_BOLD)$(COLOR_GREEN)... 🤩 philosophers compiled  ... $(COLOR_RESET)"

clean:
	$(RM) $(OBJ)
	$(RM) $(DEP)

fclean: clean
	$(RM) $(BUILD_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEP)