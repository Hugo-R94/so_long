/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/26 14:47:27 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_tile_size_n_mapsize(t_vars *v)
{
	int	rows = 0;
	int	cols = 0;
	
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
	return 0;
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
	v->t_map.map_rows = rows;
	v->t_map.map_cols = cols;
	v->moving = 0;
}

void draw_pixel_background(t_vars *v, int px, int py)
{
    int top = (int)v->player.view_y - 3;
    int bottom = (int)v->player.grid_y + 3;
    int left = (int)v->player.grid_x - 6;
    int right = (int)v->player.grid_x + 6;

    if (top < 0) top = 0;
    if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
    if (left < 0) left = 0;
    if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;

    int ty = top;
    while (ty <= bottom)
    {
        int tx = left;
        while (tx <= right)
        {
            int draw_x = (tx * v->tile_size) - (int)v->t_cam.x + px;
            int draw_y = (ty * v->tile_size) - (int)v->t_cam.y + py;

            char tile = v->t_map.map[ty][tx];
            unsigned int color = 0x000000;
			if (is_wall(tile))
			{
				if (tile == 'T')       // Top
					color = v->opt_txt.wall[0][py * v->tile_size + px];
				else if (tile == 'B')  // Bottom
					color = v->opt_txt.wall[1][py * v->tile_size + px];
				else if (tile == 'L')  // Left
					color = v->opt_txt.wall[2][py * v->tile_size + px];
				else if (tile == 'R')  // Right
					color = v->opt_txt.wall[3][py * v->tile_size + px];
				else if (tile == 'O')
					color = v->opt_txt.wall[6][py * v->tile_size + px];
				else if (tile == 'A')
					color = v->opt_txt.wall[4][py * v->tile_size + px];
				else if (tile == 'Z')
					color = v->opt_txt.wall[5][py * v->tile_size + px];
				else if (tile == 'D')
					color = v->opt_txt.wall[7][py * v->tile_size + px];
				else 
				{   
					color = v->opt_txt.ground[py * v->tile_size + px];
					put_pixel(v->frame.image, draw_x, draw_y, color);
					color = v->opt_txt.wall[8][py * v->tile_size + px];
				}
			}
            else if (tile == 'E')
            {
				color = v->opt_txt.ground[py * v->tile_size + px];
				put_pixel(v->frame.image, draw_x, draw_y, color);
				color = v->opt_txt.exit[py * v->tile_size + px];
			}
            else
                color = v->opt_txt.ground[py * v->tile_size + px];void	init_texture(t_vars *v, t_texture *txt);
			if (color != 0x000000)
				put_pixel(v->frame.image, draw_x, draw_y, color);
            tx++;
        }
        ty++;
    }
}




void	get_exit(t_vars *v)
{
	int x;
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
