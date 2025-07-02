/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:15:08 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 12:18:21 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_tile_size_n_mapsize(t_vars *v)
{
	int	rows;
	int	cols;

	rows = 0;
	cols = 0;
	while (v->t_map.map[rows])
	{
		cols = 0;
		while (v->t_map.map[rows][cols])
			cols++;
		rows++;
	}
	v->tile_size = 200;
	v->t_map.height_px = rows * v->tile_size;
	v->t_map.width_px = cols * v->tile_size;
	return (0);
}

void	calculate_offset(t_vars *v)
{
	int	rows;
	int	cols;
	int	x_map_size;
	int	y_map_size;

	rows = 0;
	cols = 0;
	while (v->t_map.map[rows])
	{
		cols = 0;
		while (v->t_map.map[rows][cols])
			cols++;
		rows++;
	}
	x_map_size = cols * v->tile_size;
	y_map_size = rows * v->tile_size;
	v->offset_x = (RES_X - x_map_size) / 2;
	v->offset_y = (RES_Y - y_map_size) / 2;
	v->t_map.map_rows = rows;
	v->t_map.map_cols = cols;
	v->moving = 0;
}

void	get_exit(t_vars *v)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (v->t_map.map[x])
	{
		y = 0;
		while (v->t_map.map[x][y])
		{
			if (v->t_map.map[x][y] == 'E')
			{
				v->exit.ex = y;
				v->exit.ey = x;
				v->exit.open = 0;
			}
			y++;
		}
		x++;
	}
}
