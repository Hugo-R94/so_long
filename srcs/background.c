/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 16:00:42 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static uint32_t	get_tile_color_wall(t_vars *v, char tile, int px, int py)
{
	uint32_t	color;

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

static unsigned int	get_tile_color(t_vars *v, char tile, int px, int py)
{
	unsigned int	color;

	color = 0x000000;
	if (is_wall(tile))
		return (get_tile_color_wall(v, tile, px, py));
	else if (tile == 'E')
		color = v->opt_txt.exit[py * v->tile_size + px];
	else
		color = v->opt_txt.ground[py * v->tile_size + px];
	return (color);
}

static void	draw_tile_pixel(t_vars *v, int *tx, int ty)
{
	int				draw_x;
	int				draw_y;
	char			tile;
	unsigned int	color;
	unsigned int	bg_color;

	draw_x = (tx[0] * v->tile_size) - (int)v->t_cam.x + tx[1];
	draw_y = (ty * v->tile_size) - (int)v->t_cam.y + tx[2];
	tile = v->t_map.map[ty][tx[0]];
	color = get_tile_color(v, tile, tx[1], tx[2]);
	if (is_wall(tile) || tile == 'E')
	{
		bg_color = v->opt_txt.ground[tx[2] * v->tile_size + tx[1]];
		put_pixel(&v->frame, draw_x, draw_y, bg_color);
	}
	if (color != 0x000000)
		put_pixel(&v->frame, draw_x, draw_y, color);
}

static void	draw_pixel_background_line(t_vars *v, int *p, int px, int py)
{
	int	tx[3];

	tx[0] = p[0];
	while (tx[0] <= p[1])
	{
		tx[1] = px;
		tx[2] = py;
		draw_tile_pixel(v, tx, p[2]);
		tx[0]++;
	}
}

void	draw_pixel_background(t_vars *v, int px, int py)
{
	int	p[3];
	int	top;
	int	bottom;

	top = (int)v->player.view_y - 3;
	bottom = (int)v->player.grid_y + 3;
	p[0] = (int)v->player.grid_x - 6;
	p[1] = (int)v->player.grid_x + 6;
	if (top < 0)
		top = 0;
	if (bottom >= v->t_map.map_rows)
		bottom = v->t_map.map_rows - 1;
	if (p[0] < 0)
		p[0] = 0;
	if (p[1] >= v->t_map.map_cols)
		p[1] = v->t_map.map_cols - 1;
	if (px < 0 || py < 0)
		return ;
	p[2] = top - 1;
	while (++p[2] <= bottom)
		draw_pixel_background_line(v, p, px, py);
}
