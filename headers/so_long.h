# ifndef SO_LONG_H
# define SO_LONG_H

#include "../minilibx-linux-master/mlx.h"
#include "../minilibx-linux-master/mlx_int.h"
#include <stdio.h>
#include "../My_libft/headers/libft.h"
#include <fcntl.h>
#include <stdlib.h>

#ifndef RES_X
# define RES_X 1280
#endif

#ifndef RES_Y
# define RES_Y 840
#endif

typedef struct s_input {
	int left;
	int right;
	int up;
	int down;
}	t_input;

typedef struct s_texture
{
	void	*wall;
	void	*ground;
	void	*coin;
	void	*player;
	void	*exit;
}	t_texture;

typedef struct s_player {
	double view_x;
	double view_y;
	int    grid_x;
	int    grid_y;
} t_player;

typedef	struct s_coin
{
	int		cx;
	int		cy;
	bool	vis;
}	t_coin;

typedef struct s_map
{
	char	**map;
	int		map_cols;
	int		map_rows;
	int 	width_px;
    int 	height_px;
}	t_map;

typedef struct s_camera {
	double x;
	double y;
	double speed;
	int limit_left;
	int limit_right;
	int limit_top;
	int limit_bottom;
} t_camera;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	void		*img;
	t_map		t_map;
	int			tile_size;
	int			offset_x;
	int			offset_y;
	bool		moving;
	int			keys[256]; // <--- pour savoir si une touche est pressée
	t_input		input;	
	t_texture	tx;
	t_player	player;
	t_camera	t_cam;
	int			coin_count;
	t_coin		*coin;
}				t_vars;

//map building and checking ----- on touche pas ca marche
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
void	initialize_still(t_vars *v);
void	render_background(t_vars *v);
void	calculate_offset(t_vars *v);
int		calculate_tile_size_n_mapsize(t_vars *v);
void	calculate_map_px_size(t_vars *v);

//player
void 	render_player(t_vars *v);
int 	key_handler_p(int keycode, t_vars *v);
void	render_frame(t_vars *v);
void	get_player_grid_pos(t_vars *v);
int		key_release_p(int keycode, t_vars *v);
int		key_handler_p(int keycode, t_vars *v);
int 	game_loop(t_vars *v);

//camera
void update_camera(t_vars *v);

//coins
void 	load_coin(t_vars *vars);
void 	render_coin(t_vars *v, t_coin *coin);
void	get_coin_count(t_vars *vars);	

#endif