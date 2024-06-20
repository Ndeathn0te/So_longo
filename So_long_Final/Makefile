# Project names
NAME = so_long

# Compiler and flags
CC = gcc
CFLAGS = -g -o -Wall -Wextra -fsanitize=address
# Source directories
SRC_DIR = src
GNL_DIR = get_next_line

# Source files
SRC_FILES = main.c map.c open_images.c controllers.c extra.c check_map.c \
			free_game.c flood_fill.c ft_itoa.c put_player.c

# Object files
OBJS = $(SRC_FILES:%.c=$(SRC_DIR)/%.o)

# MLX library path and flags
MLX_LIB = mlx
MLX_FLAGS = -L $(MLX_LIB) -lmlx -L/usr/lib/X11 -lXext -lX11

# Build rules
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_LIB) || git clone https://github.com/42Paris/minilibx-linux.git $(MLX_LIB) && $(MAKE) -C $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_DIR)/*.c $(MLX_FLAGS) -o $@

# Clean up
clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(MLX_LIB) clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re
