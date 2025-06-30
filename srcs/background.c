/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/30 13:22:16 by hugz             ###   ########.fr       */
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
static uint32_t get_tile_color_wall(t_vars *v, char tile, int px, int py)
{
	uint32_t color;
	
	if (is_wall(tile))
    {
        if (tile == 'T')
            color = v->opt_txt.wall[0][py * v->tile_size + px];
        else if (tile == 'B')
            color = v->opt_txt.wall[1][py * v->tile_size + px];
        else if (tile == 'L')
            color = v->opt_txt.wall[2][py * v->tile_size + px];
        else if (tile == 'R')
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
            color = v->opt_txt.wall[8][py * v->tile_size + px];
    }
	return (color);
}

static unsigned int get_tile_color(t_vars *v, char tile, int px, int py)
{
    unsigned int color;

    color = 0x000000;
    if (is_wall(tile))
		return (get_tile_color_wall(v, tile, px, py));
    else if (tile == 'E')
        color = v->opt_txt.exit[py * v->tile_size + px];
    else
        color = v->opt_txt.ground[py * v->tile_size + px];
    return color;
}

static void draw_tile_pixel(t_vars *v, int tx, int ty, int px, int py)
{
    int draw_x;
    int draw_y;
    char tile;
    unsigned int color;

    draw_x = (tx * v->tile_size) - (int)v->t_cam.x + px;
    draw_y = (ty * v->tile_size) - (int)v->t_cam.y + py;
    tile = v->t_map.map[ty][tx];
    color = get_tile_color(v, tile, px, py);

    if (is_wall(tile) || tile == 'E')
    {
        unsigned int bg_color;
        bg_color = v->opt_txt.ground[py * v->tile_size + px];
        put_pixel(&v->frame, draw_x, draw_y, bg_color);
    }
    if (color != 0x000000)
        put_pixel(&v->frame, draw_x, draw_y, color);
}

static void draw_pixel_background_line(t_vars *v, int ty, int left, int right, int px, int py)
{
    int tx;

    tx = left;
    while (tx <= right)
    {
        draw_tile_pixel(v, tx, ty, px, py);
        tx++;
    }
}

void draw_pixel_background(t_vars *v, int px, int py)
{
    int top;
    int bottom;
    int left;
    int right;
    int ty;

    top = (int)v->player.view_y - 3;
    bottom = (int)v->player.grid_y + 3;
    left = (int)v->player.grid_x - 6;
    right = (int)v->player.grid_x + 6;
    if (top < 0)
        top = 0;
    if (bottom >= v->t_map.map_rows)
        bottom = v->t_map.map_rows - 1;
    if (left < 0)
        left = 0;
    if (right >= v->t_map.map_cols)
        right = v->t_map.map_cols - 1;
    if (px < 0 || py < 0)
        return;
    ty = top;
    while (ty <= bottom)
    {
        draw_pixel_background_line(v, ty, left, right, px, py);
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
