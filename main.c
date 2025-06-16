#include "headers/so_long.h"

char	**getmap(int fd);
void	check_map(char **map);
void free_tab(char **map);
int	name_checker(char *str);

// int	main(void)
// {
// 	int		fd;
// 	char	**map;
// 	int		i;

// 	//MAPS INVALID
// 	char *map_duplicate_exit = "maps/invalid/duplicate_exit.ber";
// 	char *map_duplicate_player = "maps/invalid/duplicate_player.ber";
// 	char *map_empty_file = "maps/invalid/empty_file.ber";
// 	char *map_empty_line_at_start = "maps/invalid/empty_line_at_start.ber";
// 	char *map_empty_line_in_between = "maps/invalid/empty_line_in_between.ber";
// 	char *map_invalid_entities = "maps/invalid/invalid_entities.ber";
// 	char *map_no_coins = "maps/invalid/no_coins.ber";
// 	char *map_no_coins_path = "maps/invalid/no_coins_path.ber";
// 	char *map_no_corner_walls = "maps/invalid/no_corner_walls.ber";
// 	char *map_no_exit = "maps/invalid/no_exit.ber";
// 	char *map_no_exit_path = "maps/invalid/no_exit_path.ber";
// 	char *map_no_outter_walls = "maps/invalid/no_outter_walls.ber";
// 	char *map_no_player = "maps/invalid/no_player.ber";
// 	char *map_non_rectangular = "maps/invalid/non_rectangular.ber";
// 	char *map_one_character = "maps/invalid/one_character.ber";
// 	char *map_invalid5 = "maps/valid";

// 	//MAPS VALIDES
// 	char *map_minimal_horizontal = "maps/valid/minimal_horizontal.ber";
// 	char *map_minimal_vertical = "maps/valid/minimal_vertical.ber";
// 	char *map_valid1 = "maps/valid/valid1.ber";
// 	char *map_valid2 = "maps/valid/valid2.ber";
// 	char *map_valid3 = "maps/valid/valid3.ber";
// 	char *map_valid4 = "maps/valid/valid4.ber";
// 	char *map_valid5 = "maps/valid/valid5.ber";

// 	i = 0;
// 	//fd = open(map_duplicate_exit, O_RDONLY);
// 	name_checker(map_valid3);
// 	fd = open(map_valid3, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	map = getmap(fd);
// 	if (!map)
// 		return (1);
// 	while (map[i])
// 		printf("%s", map[i++]);
// 	printf("\n");
// 	printf("map checking >>>> ");
// 	check_map(map);
// 	free_tab(map);
// 	return (0);
// }

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_vars;

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_plain_put(t_vars *vars, int color)
{	
	int i;
	int j;
	
	i = 0;
	while (i <= 640)
	{
		j = 0;
		while (j < 480)
		{
			mlx_string_put(vars->mlx, vars->win, 300, 240, 0xfefffe,"string");	
			my_mlx_pixel_put(vars, i, j, color);
			j++;
		}
		i++;
	}

	return ;
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("%i",keycode);
	return (0);
}
int key_handler(int keycode, t_vars *vars)
{
    if (keycode == 65307)
	{
        ft_printf("ESCAPE\n");
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
    else if (keycode == 97 || keycode == 65361)
        ft_printf("LEFT (A / ARROW_LEFT)\n");
    else if (keycode == 100 || keycode == 65363)
        ft_printf("RIGHT (D / ARROW_RIGHT)\n");
    else if (keycode == 115 || keycode == 65364)
        ft_printf("DOWN (S / ARROW_DOWN)\n");
    else if (keycode == 119 || keycode == 65362)
        ft_printf("LEFT (W / ARROW_UP)\n");
    else
       ft_printf("%d\n", keycode);
    return (0);
}

int mouse_handler(int mousecode, int x, int y, t_vars *vars)
{
    /* x and y parameters are the pixel coordinates of the mouse
     * in the window when the event was emitted
     * you can use them to check that the user clicked in a specific region
     * of the window
     */
     if (mousecode == 1)
	 {
        ft_printf("Left Click\n");
		my_mlx_plain_put(vars, 0x0000FF); // Bleu
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	 }
     else if (mousecode == 2)
	 {
        ft_printf("Right Click\n");
		my_mlx_plain_put(vars, 0x00ff63); // vert
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	 }
     else if (mousecode == 3)
	 {
        ft_printf("Middle Click\n");
		my_mlx_plain_put(vars, 0x00FF0000); // Bleu
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	 }
     else if (mousecode == 4)
         ft_printf("Scroll UP\n");
     else if (mousecode == 5)
         ft_printf("Scroll DOWN\n");
     else if (mousecode == 6)
         ft_printf("Scroll right\n");
     else if (mousecode == 7)
         ft_printf("Scroll left\n");
     else
         ft_printf("%d\n", mousecode);
}
int	main(void)
{
		//MAPS VALIDES
	char *map_minimal_horizontal = "maps/valid/minimal_horizontal.ber";
	char *map_minimal_vertical = "maps/valid/minimal_vertical.ber";
	char *map_valid1 = "maps/valid/valid1.ber";
	char *map_valid2 = "maps/valid/valid2.ber";
	char *map_valid3 = "maps/valid/valid3.ber";
	char *map_valid4 = "maps/valid/valid4.ber";
	char *map_valid5 = "maps/valid/valid5.ber";
	t_vars	vars;
	int width = 0;
	int height = 0;
	void *chara;
	t_texture tx_set;
	char **map = NULL;
	int fd = open(map_valid3, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	map = getmap(fd);
	if (!map)
		return (1);
	check_map(map);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "SO LONG");
	if (!vars.win)
		return (1);
	vars.img = mlx_new_image(vars.mlx, 1920, 1080);
	if (!vars.img)
		return (1);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
								&vars.endian);

	tx_set = initialize_still(vars.mlx);

	
	printf("Image chargée : width=%d height=%d\n", width, height);
	render_background(vars.mlx, vars.win,tx_set,map);
	render_player(vars.mlx, vars.win, map);
	// Affiche après, pour ne pas écraser l'image XPM
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);

	//mlx_hook(vars.win, 4, 1L << 2, mouse_handler, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_handler, &vars);

	mlx_loop(vars.mlx);
	free_tab(map);
	
	return (0);
}

