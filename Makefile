# === Nom de l'exécutable ===
NAME = so_long

# === Dossiers ===
SRCS_DIR = srcs
OBJDIR = objs
LIBFT_DIR = My_libft
SO_LONG_DIR = headers
MLX_DIR = minilibx-linux-master

# === Compilation ===
CC = gcc
CFLAGS = 
INCLUDES = -I$(SO_LONG_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd -no-pie

# === Fichiers sources ===
SRCS = $(SRCS_DIR)/map.c \
	   $(SRCS_DIR)/map_checker.c \
	   $(SRCS_DIR)/map_utils.c \
	   $(SRCS_DIR)/flood_fill.c \
	   main2.c \
		$(SRCS_DIR)/init_so.c \
		$(SRCS_DIR)/player.c \
		$(SRCS_DIR)/display.c \
		$(SRCS_DIR)/coin.c 

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

$(OBJDIR)/main2.o: main2.c
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
