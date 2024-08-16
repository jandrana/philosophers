# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 15:05:47 by ana-cast          #+#    #+#              #
#    Updated: 2024/08/16 19:31:04 by ana-cast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                               COMPILATION INFO                             ##
################################################################################

NAME = philo_bonus

# Check if gcc is installed
HAS_GCC := $(shell command -v gcc 2> /dev/null)

# Check if clang is installed
HAS_CLANG := $(shell command -v clang 2> /dev/null)

ifdef HAS_CLANG
  CC = clang
else ifdef HAS_GCC
  CC = gcc
else
  $(error No compiler found)
endif

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f
PHILO = include/
DEPS = -I include

################################################################################
##                              SOURCES AND OBJECTS                           ##
################################################################################

SRC = src/main.c \
	src/init.c \
	src/parser/parse_input.c \
	src/parser/error.c \
	src/parser/split.c \
	src/threads/threads.c \
	src/threads/philo_routines.c \
	src/threads/time.c \
	src/threads/th_utils.c \
	src/utils/ft_utils.c \
	src/utils/safe_exit.c

OBJECTS = $(SRC:.c=.o)

################################################################################
##                                    COLORS                                 ##
################################################################################

END=\033[0m
BOLD=\033[1m
GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
YELLOW=\033[33m
MAGENTA=\033[35m
TURQUOISE=\033[36m

################################################################################
##                                     RULES                                  ##
################################################################################

all : head $(NAME)

head :
	@echo "$(MAGENTA)"
	@echo "\t██████  ██   ██ ██ ██       ██████  "
	@echo "\t██   ██ ██   ██ ██ ██      ██    ██ "
	@echo "\t██████  ███████ ██ ██      ██    ██ "
	@echo "\t██      ██   ██ ██ ██      ██    ██ "
	@echo "\t██      ██   ██ ██ ███████  ██████  "
	@echo "$(TURQUOISE)$(BOLD)"
	@echo "\t       B    0    N    U    $$"
	@echo "$(END)$(MAGENTA)"
	@echo "\t        42MLG: by ana-cast"
	@echo "\tProyect: \033[36m Philosophers $(MAGENTA)"
	@echo "\tCommands:\033[36m all clean fclean re $(BLUE)"
	@echo "\t🛠   Compiler: $(CC) $(END)\n"

$(NAME) : line $(OBJECTS)
	@echo "✦ ---------------------- ✦$(END)"
	@$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

%.o : %.c $(PHILO)
	@$(CC) $(FLAGS) -c $< -o $@ $(DEPS)
	@echo "$(GREEN)  ✓ Compiled: $(notdir $<)"

line :
	@echo "$(GREEN) $(BOLD)"
	@echo "  COMPILING PHILO...$(END) $(GREEN)"
	@echo "✦ ---------------------- ✦"

clean :
	@printf "\n$(YELLOW) 🗑   Removing objects$(END)"
	@$(RM) $(OBJECTS)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  objects from $(NAME) $(END)"

fclean: clean
	@printf "$(YELLOW) 🗑   Removing $(NAME) $(END)"
	@$(RM) $(NAME)
	@echo "$(GREEN)\r  ✓  $(RED)Removed  $(NAME) $(END)\n"

re :
	@$(MAKE) -s fclean
	@clear
	@$(MAKE) -s all

.PHONY: all clean fclean re