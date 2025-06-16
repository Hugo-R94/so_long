/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:02:22 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/16 16:38:30 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>


int	calculate_tile_size(int screen_width, int screen_height, char **map)
{
	int	rows = 0;
	int	cols = 0;

	while (map[rows])
	{
		cols = 0;
		while (map[rows][cols])
			cols++;
		rows++;
	}
	int	tile_w = screen_width / cols;
	int	tile_h = screen_height / rows;
	return (tile_w < tile_h) ? tile_w : tile_h;
}


t_texture	initialize_still(void *mlx_ptr)
{
	t_texture	tx_set;
	int			width;
	int			height;
	
	
	width = 100;
	height = 100;
	tx_set.wall = mlx_xpm_file_to_image(mlx_ptr, "placeholder_assets/wall.xpm", &width, &height);
	tx_set.ground = mlx_xpm_file_to_image(mlx_ptr, "placeholder_assets/ground.xpm", &width, &height);
	tx_set.coin = mlx_xpm_file_to_image(mlx_ptr, "placeholder_assets/coin.xpm", &width, &height);
	tx_set.player = mlx_xpm_file_to_image(mlx_ptr, "placeholder_assets/player.xpm", &width, &height);
	tx_set.exit = mlx_xpm_file_to_image(mlx_ptr, "placeholder_assets/exit.xpm", &width, &height);

	return (tx_set);
}
void	calculate_offset(int height, int width, char **map, int tilesize, int *offset_x,int *offset_y)
{
	int	rows = 0;
	int	cols = 0;
	int x_map_size;
	int y_map_size;
	
	while (map[rows])
	{
		cols = 0;
		while (map[rows][cols])
			cols++;
		rows++;
	}
	x_map_size = cols * tilesize;
	y_map_size = rows * tilesize;
	*offset_x = (height - x_map_size)/2;
	*offset_y = (width - y_map_size)/2;
}

void	render_background(void *mlx_ptr,void *win_ptr, t_texture tx_set, char **map)
{
	int	i;
	int j;
	int tile_size;
	int offset_x;
	int offset_y;
	
	j = 0;
	i = 0;
	tile_size = calculate_tile_size(1920, 1080, map);
	calculate_offset(1920, 1080, map, tile_size, &offset_x, &offset_y);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(map[i][j] == '1' )
			
			mlx_put_image_to_window(mlx_ptr,win_ptr,tx_set.wall,(j * tile_size)+offset_x,(i * tile_size)+offset_y);
			else if(map[i][j] == 'E')
				mlx_put_image_to_window(mlx_ptr,win_ptr,tx_set.exit,(j * tile_size)+offset_x,(i * tile_size)+offset_y);
			else if(map[i][j] !='\n')
				mlx_put_image_to_window(mlx_ptr,win_ptr,tx_set.ground,(j * tile_size)+offset_x,(i * tile_size)+offset_y);
			
			j++;
		}
		i++;
	}
	
}