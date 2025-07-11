/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:54:57 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/04 13:23:12 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	name_error(t_vars *vars)
{
	free(vars);
	ft_putstr_fd("Error\nfd error.\n", 2);
	exit(EXIT_FAILURE);
}

void	init_vars(t_vars *vars, char *map_path)
{
	int	fd;

	name_checker(map_path);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		name_error(vars);
	vars->t_map.map = getmap(fd);
	close(fd);
	if (!vars->t_map.map)
		error_map(vars->t_map.map, vars);
	check_map(vars->t_map.map, vars);
	vars->t_map.map = remap(vars->t_map.map);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		error_exit(vars);
	vars->win = mlx_new_window(vars->mlx, RES_X, RES_Y, "SO LONG");
	if (!vars->win)
		error_exit(vars);
	vars->img = mlx_new_image(vars->mlx, RES_X, RES_Y);
	if (!vars->img)
		error_exit(vars);
	init_all(vars);
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc != 2)
		return (1);
	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (1);
	init_vars(vars, argv[1]);
	mlx_hook(vars->win, 2, 1L << 0, key_pressed_p, vars);
	mlx_hook(vars->win, 3, 1L << 1, key_release_p, vars);
	mlx_hook(vars->win, 17, 0, clean_and_exit, vars);
	mlx_loop_hook(vars->mlx, game_loop, vars);
	mlx_loop(vars->mlx);
	clean_and_exit(vars);
	return (0);
}
