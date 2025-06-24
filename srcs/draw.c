/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:51:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/24 18:00:53 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned int	get_pixel(t_img *img, int x, int y)
{
	if (!img || !img->data)
		return (0x000000);
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0x000000); // noir si hors limites

	int	offset = y * img->size_line + x * (img->bpp / 8);
	return (*(unsigned int *)(img->data + offset));
}

void	put_pixel(t_img *img, int x, int y, unsigned int color)
{
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return;

	int	offset = y * img->size_line + x * (img->bpp / 8);
	*(unsigned int *)(img->data + offset) = color;
}

void	draw_image(t_img *dst, t_img *src, int dst_x, int dst_y)
{
	int	x, y;
	unsigned int color;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			color = get_pixel(src, x, y);
			if (color != 0x000000) // ignore la transparence noire
				put_pixel(dst, dst_x + x, dst_y + y, color);
			x++;
		}
		y++;
	}
}
void	draw_tx_tile(t_vars *v, uint32_t *tx, int dst_x, int dst_y)
{
	int			x;
	int			y;
	uint32_t	color;

	x = 0;
	while (x < v->tile_size)
	{
		y = 0;
		while (y < v->tile_size)
		{
			color = tx[x * v->tile_size + y];
			if (color != 0x000000)
				put_pixel(v->frame.image, dst_x + x, dst_y + y, color);
			y++;
		}
		x++;
	}
}
// void draw_frame(t_img *dst, t_vars *v, int dst_x, int dst_y)
// {
// 	int top = v->player.grid_y - 4;
// 	int bottom = v->player.grid_y + 4;
// 	int left = v->player.grid_x - 4;
// 	int right = v->player.grid_x + 4;

// 	if (top < 0) top = 0;
// 	if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
// 	if (left < 0) left = 0;
// 	if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;

// 	while (top < bottom)
// 	{
// 		while (left < right)
// 		{
// 			int draw_x = top * v->tile_size - (int)v->t_cam.x;
// 			int draw_y = left * v->tile_size - (int)v->t_cam.y;
// 			char tile = v->t_map.map[top][left];
// 			if (tile == '1')
// 				draw_tx_tile(v, v->opt_txt.wall, draw_x, draw_y);
// 			else if (tile == '0')
// 				draw_tx_tile(v, v->opt_txt.ground, draw_x, draw_y);
// 			else if (tile == 'E')
// 				draw_tx_tile(v, v->opt_txt.exit, draw_x, draw_y);
// 			if (tile == 'C')
// 				draw_tx_tile(v, v->opt_txt.coin, draw_x, draw_y);
// 			left++;
// 		}
// 		top++;
// 	}

// 	int px = v->player.view_x - (int)v->t_cam.x;
// 	int py = v->player.view_y - (int)v->t_cam.y;
// 	draw_tx_tile(v, v->opt_txt.player, px, py);
// }


void draw_frame(t_img *dst, t_vars *v, int dst_x, int dst_y)
{
    for (int py = 0; py < v->tile_size; py++)
    {
        for (int px = 0; px < v->tile_size; px++)
            draw_pixel_background(v, px, py);
    }
for (int py = 0; py < v->tile_size; py++)
    {
        for (int px = 0; px < v->tile_size; px++)
        {
			draw_pixel_mob(v, px, py);
            draw_pixel_coins(v, px, py);
        }
    }
    for (int py = 0; py < v->tile_size; py++)
    {
        for (int px = 0; px < v->tile_size; px++)
        {
			draw_pixel_shadow(v, px, py);
			draw_pixel_player(v, px, py);
        }
    }
}
