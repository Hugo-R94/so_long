# === Nom de l'exécutable ===
NAME = so_long

# === Dossiers ===
SRCS_DIR = srcs
HEADERS_DIR = HEADERS
LIBFT_DIR = My_libft

# === Compilation ===
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_DIR)

# === Fichiers sources ===
SRCS = $(SRCS_DIR)/map.c
LIBFT = $(LIBFT_DIR)/libft.a

# === Règles ===
all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror -fPIC"

clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
