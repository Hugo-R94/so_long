# ifndef SO_LONG_H
# define SO_LONG_H

#include "../minilibx-linux-master/mlx.h"
#include "../minilibx-linux-master/mlx_int.h"
#include <stdio.h>
#include "../My_libft/headers/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>

#ifndef RES_X
# define RES_X 1920
#endif

#ifndef RES_Y
# define RES_Y 1080
#endif

typedef struct s_input {
	int left;
	int right;
	int up;
	int down;
}	t_input;

typedef struct s_wall_textures {
    t_img top;
    t_img bottom;
    t_img left;
    t_img right;
    t_img corner_tl;
    t_img corner_tr;
    t_img corner_bl;
    t_img corner_br;
    t_img middle; // chaise pliante par exemple
} t_wall_textures;

typedef struct s_opt_tx
{
	uint32_t	*player;
	uint32_t	*ground;
	uint32_t	*coin;
	uint32_t	*exit;
	uint32_t	*shadow;
	uint32_t	*wall[10];
	uint32_t	*mob;
} t_opt_tx;

typedef struct s_texture
{
	t_wall_textures	wall;
	t_img	ground;
	t_img	coin;
	t_img	player;
	t_img	exit;
	t_img	shadow;
	t_img	mob;
}	t_texture;


typedef struct s_player {
	double view_x;
	double view_y;
	double view_jump;
	int    grid_x;
	int    grid_y;
	int		jump;
	double	jump_counter;
	double	vel_x;
	double	vel_y;
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

typedef struct s_exit
{
	int		open;
	int		ex;
	int		ey;
}	t_exit;

typedef struct s_mob
{
	bool	vis;
	int		mx;
	int		my;
	char	axis;
	int		dir;
	double		view_x;
	double 	view_y;
}	t_mob;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	void		*img;
	t_map		t_map;
	int			tile_size;
	int			offset_x;//peut etre a supprimer
	int			nb_mob;
	t_mob		*mob;
	int			offset_y;
	bool		moving;
	int			keys[256]; // <--- pour savoir si une touche est pressée
	t_exit		exit;
	t_input		input;	
	t_texture	tx;
	t_opt_tx	opt_txt;
	t_player	player;
	t_camera	t_cam; 
	int			coin_count;
	int			coin_get;
	t_coin		*coin;
	t_img		frame;
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

//initialize func
void	init_all(t_vars *v);
//init texture func
void	init_img_struct(t_img *txt);
void	get_img(t_vars *v, t_img *img, const char *txt_name);
void	init_texture(t_vars *v, t_texture *txt);
uint32_t *opt_texture(t_img *img, t_vars *v);
void	transfer_tx(t_vars *v);

//remap
char	**remap(char **map);
char 	set_wall(char **map, int y, int x, int rows, int cols);

//image drawing with alpha
unsigned int	get_pixel(t_img *img, int x, int y);
void			put_pixel(t_img *img, int x, int y, unsigned int color);
void			draw_image(t_img *dst, t_img *src, int dst_x, int dst_y);
//background
int	calculate_tile_size_n_mapsize(t_vars *v);
void	calculate_offset(t_vars *v);
void	draw_background(t_vars *v, t_img *dst);
void draw_pixel_background(t_vars *v, int px, int py);
int 	is_wall(char c);
//camera 
void update_camera(t_vars *v);
int init_frame(t_vars *v, t_img *frame, int width, int height);
void render_frame(t_vars *v);

//player
void get_player_grid_pos(t_vars *v);
void draw_player(t_vars *v);
void	draw_shadow(t_vars *v);
void draw_pixel_player(t_vars *v, int x, int y);
void draw_pixel_shadow(t_vars *v, int x, int y);

//player mouvements
void	move_player(t_vars *vars, double dx, double dy);
void	key_pressed_p(int keycode, t_vars *v);
void	key_release_p(int keycode, t_vars *v);
void	game_loop(t_vars *v);
void	player_jump(t_vars *v);

//coins
void	get_coin_count(t_vars *vars);
void 	load_coin(t_vars *vars);
void	init_coins(t_vars *v);
void draw_coin(t_vars *v, int index);
void draw_pixel_coins(t_vars *v, int x, int y);

//exit
void	get_exit(t_vars *v);
void	draw_frame(t_img *dst, t_vars *v, int dst_x, int dst_y);

//mob
void	draw_pixel_mob(t_vars *v, int x, int y);
void	nb_mob(t_vars *v);
void	set_ennemy(t_vars *v, t_mob *mob, int x, int y);
void	set_all_ennemy(t_vars *v);
void	set_mouv_axis(t_vars *v, t_mob *mob);
void mouv_all_mob(t_vars *v);
void mouv_mob_simple(t_vars *v);



#endif