# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caymard <caymard@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/02 23:04:50 by lolemmen          #+#    #+#              #
#    Updated: 2024/06/24 19:38:57 by caymard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
.PHONY: NAME re all fclean clean

NAME = cub3d

# Compilation

RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -ggdb3 #-fsanitize=address

# Detect the operating system
ifeq ($(shell uname), Linux)
	MLX_DIR = ./mlx_linux
	MLX_PATH = mlx_linux/libmlx.a
	MLX =  -L /usr/lib -lXext -lX11 -lm -lz 
	MLX_OBJ = -I/usr/include -Imlx_linux -O3
else
	MLX_DIR = ./mlx
	MLX_PATH = mlx/libmlx.a	
	MLX = -lmlx -Lmlx -framework OpenGl -framework AppKit
	MLX_OBJ = -Imlx -c
endif
 
MLX_LIB = -L $(MLX_DIR) -lmlx

# Directories

SRCSDIR = srcs
INCSDIR = includes
OBJSDIR = objs

# Sources

#INC = 



MAIN = main.c utils.c
ERROR = errors.c
HOOK = key_hooks.c mouse_hooks.c
MAP = get_sizes.c map_init.c map_size.c nodes_type.c
NODE = doors.c node_api.c node_creation.c node_utils.c
PLAYER = player_init.c
#RC = pixel_renew.c rc_vecteurs.c window_img.c
RC = pixel_renew.c raycast.c window_img.c
#RC = pixel_renew.c rc_base.c window_img.c
LIBFT = ft_isdigit.c ft_itoa.c ft_printf_putter.c ft_printf.c ft_strjoin.c ft_substr.c

SRC =	$(MAIN) \
		$(addprefix error_manager/,$(ERROR)) \
		$(addprefix hooks_manager/,$(HOOK)) \
		$(addprefix map_manager/,$(MAP)) \
		$(addprefix node_manager/,$(NODE)) \
		$(addprefix player_manager/,$(PLAYER)) \
		$(addprefix Raycast/,$(RC)) \
		$(addprefix libft/,$(LIBFT))

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
INCS = $(addprefix -I, $(INCS_DIR)) $(MLX_INCS)

all : $(NAME)

$(NAME) : $(OBJS)
	echo "$(LOG_CLEAR)$(NAME)... $(LOG_CYAN)assembling... $(LOG_NOCOLOR)$(LOG_UP)"
	cc $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX) -o $(NAME)
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