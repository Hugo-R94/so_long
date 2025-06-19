/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:51:14 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/19 12:48:49 by hrouchy          ###   ########.fr       */
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
			//printf("y = %i | x = %i\n",y,x);
			if (color != 0x000000) // ignore la transparence noire
				put_pixel(dst, dst_x + x, dst_y + y, color);
			x++;
		}
		y++;
	}
}

