/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:51:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/01 14:20:25 by hrouchy          ###   ########.fr       */
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

void put_pixel(t_img *img, int x, int y, uint32_t color)
{
    if (!img || !img->data || x < 0 || y < 0)
    {
        return;
    }
    
    if (x < 0 || y < 0 || x >= img->width || y >= img->height)
        return;
    int offset = y * img->size_line + x * (img->bpp / 8);
    *(unsigned int *)(img->data + offset) = color;
	
}

void    draw_bg(t_vars *v)
{
    int py;
    int px;
        
	py = 0;
    while (py < v->tile_size)
    {
        px = 0;
        while (px < v->tile_size)
            draw_pixel_background(v, px++, py);
        py++;
    }
	py = 0;
    py = 0;
    while (py < v->tile_size)
    {
        px = 0;
        while (px < v->tile_size)
        {
            draw_pixel_mob(v, px, py);
            draw_pixel_coins(v, px, py);
            draw_pixel_shadow(v, px, py);
            px++;
        }
        py++;
    }
}

void draw_frame(t_vars *v)
{
    int py;
	int px;
    
	py = 0;
    draw_bg(v);
    while (py < v->tile_size)
    {
        px = 0;
        while (px < v->tile_size)
            draw_pixel_player(v, px++, py);
        py++;
    }
}

