# === Nom de l'exécutable ===
NAME = so_long

# === Dossiers ===
SRCS_DIR = srcs
OBJDIR = objs
LIBFT_DIR = My_libft
SO_LONG_DIR = headers
MLX_DIR = minilibx-linux

# === Compilation ===
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -I$(SO_LONG_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -no-pie

# === Fichiers sources ===
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
		so_long.c 

# === Objets dans le dossier objs ===
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:srcs/%=$(OBJDIR)/%)

# === Librairies ===
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# === Règles ===
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Compilation des .o en respectant le dossier objs/
$(OBJDIR)/%.o: srcs/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/so_long.o: so_long.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
