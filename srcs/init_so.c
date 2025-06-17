/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_so.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:23 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/17 18:04:16 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_tile_size_n_mapsize(t_vars *v)
{
	int	rows = 0;
	int	cols = 0;
	int tile_w;
	int tile_h;
	int ret;
	
	while (v->t_map.map[rows])
	{
		cols = 0;
		while (v->t_map.map[rows][cols])
			cols++;
		rows++;
	}
	tile_w = RES_X / cols;
	tile_h = RES_Y / rows;
	v->tile_size = 100;
	v->t_map.height_px = rows * v->tile_size;
	v->t_map.width_px = cols * v->tile_size;
	// if (tile_h > tile_w) //a integrer plus tard
	// 	ret = tile_h;
	// else
	// 	ret = tile_w;
	// if (ret < 500 && ret >= 250)
	// 	v->tile_size = 250;
	// else if (tile_h < 250)
	// 	v->tile_size = 125;
	// else
	// 	v->tile_size = 500;
}
void	calculate_offset(t_vars *v)
{
	int	rows = 0;
	int	cols = 0;
	int x_map_size;
	int y_map_size;
	
	while (v->t_map.map[rows])
	{
		cols = 0;
		while (v->t_map.map[rows][cols])
			cols++;
		rows++;
	}
	x_map_size = cols * v->tile_size;
	y_map_size = rows * v->tile_size;
	v->offset_x = (RES_X - x_map_size)/2;
	v->offset_y = (RES_Y- y_map_size)/2;
}
// calculate_map_px_size(t_vars *v)
// {
// 	int	map_size;
	
// 	map_size = v->tile_size *v->
// }

void	initialize_still(t_vars *v)
{
	int			size;

	size = v->tile_size;
	v->tx.wall = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/wall.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: wall.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.ground = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/ground.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: ground.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.coin = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/coin_0.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: coin.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.player = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/player.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: hulk_still.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.exit = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/exit.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: exit.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
}

void	render_background(t_vars *v)
{
	int	i;
	int j;
	int draw_x;
	int draw_y;

	i = 0;
	while (v->t_map.map[i])
	{
		j = 0;
		while (v->t_map.map[i][j])
		{
			draw_x = (j * v->tile_size) - (int)v->t_cam.x;
			draw_y = (i * v->tile_size) - (int)v->t_cam.y;

			if (v->t_map.map[i][j] == '1')
				mlx_put_image_to_window(v->mlx, v->win, v->tx.wall, draw_x, draw_y);
			else if (v->t_map.map[i][j] == 'E')
				mlx_put_image_to_window(v->mlx, v->win, v->tx.exit, draw_x, draw_y);
			else if (v->t_map.map[i][j] != '\n')
				mlx_put_image_to_window(v->mlx, v->win, v->tx.ground, draw_x, draw_y);

			j++;
		}
		i++;
	}
}
