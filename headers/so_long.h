# ifndef SO_LONG_H
# define SO_LONG_H

#include "../minilibx-linux-master/mlx.h"
#include "../minilibx-linux-master/mlx_int.h"
#include <stdio.h>
#include "../My_libft/headers/libft.h"
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_texture
{
	void	*wall;
	void	*ground;
	void	*coin;
	void	*player;
	void	*exit;
}	t_texture;


//map building and checking
int		flood_fill_element(char **map, int x, int y, char element);
char	**clone_map(char **map);
void	find_player(char **map, int *x, int *y);
void	check_path(char **map);
int		check_invalid(char **map);
void	check_map(char **map);
void	error_ff(char **map, char **clonemap);
int		ft_strcmp(char *s1, char *s2);
void	error_map(char **map);
int		count_element(char **map, char element);
void	free_tab(char **map);
char	*ft_strcpy(char *dest, char *src);
char	**ft_realloc(char **map, int size);
int		name_checker(char *str);
char	**getmap(int fd);

//initialise texture
t_texture	initialize_still(void *mlx_ptr);
void	render_background(void *mlx_ptr,void *wint_ptr, t_texture tx_set, char **map);
void	calculate_offset(int height, int width, char **map, int tilesize, int *offset_x,int *offset_y);
int		calculate_tile_size(int screen_width, int screen_height, char **map);

//player
void render_player(void *mlx_ptr,void *win_ptr, char **map);
#endif