# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jetol <jetol@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/02 23:04:50 by lolemmen          #+#    #+#              #
#    Updated: 2024/07/03 19:02:29 by jetol            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
.PHONY: NAME re all fclean clean

NAME = cub3d

# Compilation

RM = rm -rf
CC = gcc
CFLAGS = -fsanitize=address -g#-Wall -Werror -Wextra 

# Directories

SRCSDIR = srcs
INCSDIR = includes
OBJSDIR = objs

# Sources

INC = 

SRC = \
	debug.c \
	 main.c \
		utils.c \
		map_manager/nodes_type.c \
		map_manager/get_sizes.c \
		map_manager/map_init.c \
		map_manager/map_size.c \
		node_manager/node_creation.c \
		node_manager/node_api.c \
		node_manager/node_utils.c \
		node_manager/doors.c \
		error_manager/errors.c \
		player_manager/player_init.c \
		hooks_manager/key_hooks.c \
		hooks_manager/mouse_hooks.c \
		hooks_manager/init_hooks.c

# **************************************************************************** #

# Special Chars

LOG_CLEAR = \033[2K
LOG_UP = \033[A
LOG_NOCOLOR = \033[0m
LOG_BLACK = \033[1;30m
LOG_RED = \033[1;31m
LOG_GREEN = \033[1;32m
LOG_YELLOW = \033[1;33m
LOG_BLUE = \033[1;34m
LOG_VIOLET = \033[1;35m
LOG_CYAN = \033[1;36m
LOG_WHITE = \033[1;37m

# **************************************************************************** #

SRCS = $(addprefix $(SRCSDIR)/, $(SRC))
OBJS = $(addprefix $(OBJSDIR)/, $(addsuffix .o, $(basename $(SRC))))
OBJS_DIR = $(sort $(dir $(OBJS)))

INCS_DIR = $(addsuffix /, $(INCSDIR))
INCS = $(addprefix -I, $(INCS_DIR)) -Ilibft -Imlx

all : $(NAME)

$(NAME) : $(OBJS)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_CYAN)assembling... $(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) $(CFLAGS) $(OBJS) -Llibft -Lmlx -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_GREEN)compiled $(LOG_GREEN)✓$(LOG_NOCOLOR)"

clean :
	$(RM) $(OBJS_DIR)
	$(RM) $(OBJSDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

norm :
	norminette

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	mkdir -p $(OBJSDIR) $(OBJS_DIR)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_YELLOW)$<$(LOG_NOCOLOR)$(LOG_UP)"
	$(CC) -c $< -o $@ $(INCS) $(CFLAGS)