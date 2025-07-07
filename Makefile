#EXE
NAME = so_long

#COLORS
YELLOW	= \033[1;33m
RESET	= \033[0m

#DIR
SRCS_DIR = srcs
OBJDIR = objs
LIBFT_DIR = My_libft
INCLUDE_DIR = headers
MLX_DIR = minilibx-linux

#CC
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -no-pie

#FILES
SRCS =  $(SRCS_DIR)/map.c \
		$(SRCS_DIR)/map_checker.c \
		$(SRCS_DIR)/map_utils.c \
		$(SRCS_DIR)/flood_fill.c \
		$(SRCS_DIR)/background.c \
		$(SRCS_DIR)/init.c \
		$(SRCS_DIR)/init1.c \
		$(SRCS_DIR)/player.c \
		$(SRCS_DIR)/camera.c \
		$(SRCS_DIR)/draw.c \
		$(SRCS_DIR)/coin.c \
		$(SRCS_DIR)/player_mov.c \
		$(SRCS_DIR)/loop.c \
		$(SRCS_DIR)/gameloop.c \
		$(SRCS_DIR)/remap.c \
		$(SRCS_DIR)/mob.c \
		$(SRCS_DIR)/mob_mouv.c \
		$(SRCS_DIR)/mob_mouv1.c \
		$(SRCS_DIR)/mob_mouv2.c \
		$(SRCS_DIR)/cleanup.c \
		$(SRCS_DIR)/ft_sprintf.c \
		$(SRCS_DIR)/background_utils.c \
		$(SRCS_DIR)/cleanup_utils.c \
		$(SRCS_DIR)/cleanup_utils2.c \
		$(SRCS_DIR)/cleanup_tx.c \
		$(SRCS_DIR)/so_long.c

#OBJS
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJDIR)/%.o)

#LIB
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

#RULES
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo -e "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
