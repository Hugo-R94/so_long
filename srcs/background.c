/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/19 16:48:56 by hrouchy          ###   ########.fr       */
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

void draw_x_wall(t_img *dst, t_vars *v, int x, int y)
{
	int draw_x = (y * v->tile_size) - (int)v->t_cam.x;
	int draw_y = (x * v->tile_size) - (int)v->t_cam.y;

	int rows = v->t_map.map_rows;
	int cols = v->t_map.map_cols;

	if ((x + 1 < rows && y + 1 < cols && v->t_map.map[x + 1][y] == '1' && v->t_map.map[x][y + 1] == '1') ||
		(x - 1 >= 0 && y + 1 < cols && v->t_map.map[x - 1][y] == '1' && v->t_map.map[x][y + 1] == '1') ||
		(x - 1 >= 0 && y - 1 >= 0 && v->t_map.map[x - 1][y] == '1' && v->t_map.map[x][y - 1] == '1') ||
		(x + 1 < rows && y - 1 >= 0 && v->t_map.map[x + 1][y] == '1' && v->t_map.map[x][y - 1] == '1'))
	{
		draw_image(dst, &v->tx.wall.corner, draw_x, draw_y);
	}
	else if (x == 0)
		draw_image(dst, &v->tx.wall.top, draw_x, draw_y);
	else if (x == rows - 1)
		draw_image(dst, &v->tx.wall.bottom, draw_x, draw_y);
	else if (y == 0)
		draw_image(dst, &v->tx.wall.left, draw_x, draw_y);
	else if (y == cols - 1)
		draw_image(dst, &v->tx.wall.right, draw_x, draw_y);
	else
		draw_image(dst, &v->tx.wall.middle, draw_x, draw_y); // 💺 Chaise pliante ici
}



void draw_background(t_vars *v, t_img *dst)
{
    int i, j;
    int count = 0;

    if (!v->tx.wall.top.image || !v->tx.wall.bottom.image || !v->tx.wall.left.image ||
        !v->tx.wall.right.image || !v->tx.wall.corner.image)
    {
        ft_printf("⚠️ Une texture mur ou corner est NULL\n");
        return;
    }

    i = 0;
    while (v->t_map.map[i])
    {
        j = 0;
        while (v->t_map.map[i][j])
        {
            if (v->t_map.map[i][j] == '1')
            {
				int draw_x = (j * v->tile_size) - (int)v->t_cam.x;
                int draw_y = (i * v->tile_size) - (int)v->t_cam.y;
                // Ici on passe les indices map, pas les pixels
                draw_x_wall(dst, v, i, j);
			  // draw_image(dst, &v->tx.wall.top, draw_x, draw_y);
                count++;
            }
            else if (v->t_map.map[i][j] == 'E')
            {
                int draw_x = (j * v->tile_size) - (int)v->t_cam.x;
                int draw_y = (i * v->tile_size) - (int)v->t_cam.y;
                draw_image(dst, &v->tx.exit, draw_x, draw_y);
                count++;
            }
            else if (v->t_map.map[i][j] != '\n')
            {
                int draw_x = (j * v->tile_size) - (int)v->t_cam.x;
                int draw_y = (i * v->tile_size) - (int)v->t_cam.y;
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