/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:54:57 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/23 16:12:20 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/so_long.h"

int	main(void)
{
	int		fd;
	int		i;
	t_vars *vars;
	//MAPS INVALID
	char *map_duplicate_exit = "maps/invalid/duplicate_exit.ber";
	char *map_duplicate_player = "maps/invalid/duplicate_player.ber";
	char *map_empty_file = "maps/invalid/empty_file.ber";
	char *map_empty_line_at_start = "maps/invalid/empty_line_at_start.ber";
	char *map_empty_line_in_between = "maps/invalid/empty_line_in_between.ber";
	char *map_invalid_entities = "maps/invalid/invalid_entities.ber";
	char *map_no_coins = "maps/invalid/no_coins.ber";
	char *map_no_coins_path = "maps/invalid/no_coins_path.ber";
	char *map_no_corner_walls = "maps/invalid/no_corner_walls.ber";
	char *map_no_exit = "maps/invalid/no_exit.ber";
	char *map_no_exit_path = "maps/invalid/no_exit_path.ber";
	char *map_no_outter_walls = "maps/invalid/no_outter_walls.ber";
	char *map_no_player = "maps/invalid/no_player.ber";
	char *map_non_rectangular = "maps/invalid/non_rectangular.ber";
	char *map_one_character = "maps/invalid/one_character.ber";
	char *map_invalid5 = "maps/valid";

	//MAPS VALIDES
	char *map_minimal_horizontal = "maps/valid/minimal_horizontal.ber";
	char *map_minimal_vertical = "maps/valid/minimal_vertical.ber";
	char *map_valid1 = "maps/valid/valid1.ber";
	char *map_valid2 = "maps/valid/valid2.ber";
	char *map_valid3 = "maps/valid/valid3.ber";
	char *map_valid4 = "maps/valid/valid4.ber";
	char *map_valid5 = "maps/valid/valid5.ber";

	// allocation de vars
	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (1);

	i = 0;
	name_checker(map_valid1);
	fd = open(map_valid1, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	vars->t_map.map = getmap(fd);
	vars->t_map.width_px = vars->t_map.map_cols * vars->tile_size;
	vars->t_map.height_px = vars->t_map.map_rows * vars->tile_size;
	if (!vars->t_map.map)
		return (1);
	// while (vars->t_map.map[i])
	// 	printf("%s", vars->t_map.map[i++]);
	
	printf("map checking >>>> ");
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_printf("vars mlx failed.");
		return (1);
	}
	vars->win = mlx_new_window(vars->mlx, RES_X, RES_Y, "SO LONG");
	if (!vars->win)
		return (1);
	vars->img = mlx_new_image(vars->mlx, RES_X, RES_Y);
	if (!vars->img)
		return (1);
	check_map(vars->t_map.map);
	vars->t_map.map = remap(vars->t_map.map);
	while (vars->t_map.map[i])
		printf("%s", vars->t_map.map[i++]);
	printf("\n");
	init_all(vars);
	
	// printf("offsetx = %i | offset_y = %i\n ",vars->offset_x,vars->offset_y);
	// printf("cam x = %f | cam y = %f\n",vars->t_cam.x,vars->t_cam.y);
	//render_frame(vars);
	
	mlx_hook(vars->win, 2, 1L << 0, key_pressed_p, vars);     // key down
	mlx_hook(vars->win, 3, 1L << 1, key_release_p, vars);   // key up
	mlx_loop_hook(vars->mlx, game_loop, vars);           // loop appelée à chaque "frame"
	mlx_loop(vars->mlx);
	return 0;
}