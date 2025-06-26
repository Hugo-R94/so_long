/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:51:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/26 18:02:31 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned int	get_pixel(t_img *img, int x, int y)
{
	if (!img || !img->data)
		return (0x000000);
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0x000000);

	int	offset = y * img->size_line + x * (img->bpp / 8);
	return (*(unsigned int *)(img->data + offset));
}

void put_pixel(t_img *img, int x, int y, unsigned int color)
{
	 int offset;
    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return;
    offset = y * img->size_line + x * (img->bpp / 8);
    *(unsigned int *)(img->data + offset) = color;
	//printf("x = %i | y = %i | color = 0x%x | img width = %i | img height = %i | size line = %i | offset = %i | img bpp = %i\n",
     //  x, y, color, img->width, img->height, img->size_line, offset, img->bpp);

}


void	draw_image(t_img *dst, t_img *src, int dst_x, int dst_y)
{
	int	x;
	int y;
	unsigned int color;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			color = get_pixel(src, x, y);
			if (color != 0x000000) 
				put_pixel(dst, dst_x + x, dst_y + y, color);
			x++;
		}
		y++;
	}
}

// void	draw_tx_tile(t_vars *v, uint32_t *tx, int dst_x, int dst_y)
// {
// 	int			x;
// 	int			y;
// 	uint32_t	color;

// 	x = 0;
// 	while (x < v->tile_size)
// 	{
// 		y = 0;
// 		while (y < v->tile_size)
// 		{
// 			color = tx[x * v->tile_size + y];
// 			if (color != 0x000000)
// 				put_pixel(v->frame.image, dst_x + x, dst_y + y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void draw_frame(t_img *dst, t_vars *v)
{
    int py;
	
	py = 0;
    while (py < v->tile_size)
    {
        int px = 0;
        while (px < v->tile_size)
            draw_pixel_background(v, px++, py);
        py++;
    }
	py = 0;
    while (py < v->tile_size)
    {
        int px = 0;
        while (px < v->tile_size)
        {
			
            draw_pixel_mob(v, px, py);
            draw_pixel_coins(v, px, py);
            draw_pixel_shadow(v, px, py);
            px++;
        }
        py++;
    }
	py = 0;
    while (py < v->tile_size)
    {
        int px = 0;
        while (px < v->tile_size)
            draw_pixel_player(v, px++, py);
        py++;
    }
}
