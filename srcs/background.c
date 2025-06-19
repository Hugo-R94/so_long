/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/19 14:24:41 by hrouchy          ###   ########.fr       */
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
	v->moving = 0;
}

void draw_background(t_vars *v, t_img *dst)
{
    int i, j, draw_x, draw_y;
    int count = 0;

    i = 0;
    while (v->t_map.map[i])
    {
        j = 0;
        while (v->t_map.map[i][j])
        {
            draw_x = (j * v->tile_size) - (int)v->t_cam.x;
            draw_y = (i * v->tile_size) - (int)v->t_cam.y;

            if (v->t_map.map[i][j] == '1')
            {
                draw_image(dst, &v->tx.wall, draw_x, draw_y);
                count++;
				 if (!v->tx.wall.image || !v->tx.wall.data)
				{
					ft_printf("wall texture NULL dans wall\n");
					return;
				}
            }
            else if (v->t_map.map[i][j] == 'E')
            {
                draw_image(dst, &v->tx.exit, draw_x, draw_y);
                count++;
            }
            else if (v->t_map.map[i][j] != '\n')
            {
                draw_image(dst, &v->tx.ground, draw_x, draw_y);
                count++;
            }
            j++;
        }
        i++;
    }
    ft_printf("Tiles drawn in background: %d\n", count);
}
void	get_exit(t_vars *v)
{
	int x;
	int	y;
	
	x = 0;;
	y = 0;
	while (v->t_map.map[x])
	{
		y = 0;
		while (v->t_map.map[x][y])
		{
			
			if (v->t_map.map[x][y] == 'E')
			{
				v->exit.ex = x;
				v->exit.ey = y;
				v->exit.open = 0;
			}	
			y++;
		}
		x++;
	}
	
}