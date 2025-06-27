/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/27 12:49:47 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_vars *v)
{
	v->player.vel_x = 0;
	v->player.vel_y = 0;
	v->player.jump = 0;
	v->player.jump_counter = 0;
	v->input.left = 0;
	v->input.right = 0;
	v->input.up = 0;
	v->input.down = 0;
	v->opt_txt.index_p = 0;
}

void get_player_grid_pos(t_vars *v)
{
	int y = 0;
	while (v->t_map.map[y])
	{
		int x = 0;
		while (v->t_map.map[y][x])
		{
			if (v->t_map.map[y][x] == 'P')
			{
				v->player.grid_x = x;
				v->player.grid_y = y;
				v->player.view_x = (double)x;
				v->player.view_y = (double)y;
				v->player.view_jump = (double)y;
				init_player(v);
				return;
			}
			x++;
		}
		y++;
	}
}

// void draw_player(t_vars *v)
// {
//     int px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
//     int py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y;

//     if (!v->tx.player.image || !v->tx.player.data)
//     {
//         ft_printf("player texture NULL dans render_player\n");
//         return;
//     }
//     draw_image(&v->frame, &v->tx.player, px, py);
// }

// void	draw_shadow(t_vars *v)
// {
// 	 int px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
//    	 int py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y ;
// 	 draw_image(&v->img, &v->tx.shadow, px, py);
// }
// void draw_pixel_player(t_vars *v, int x, int y)
// {
// 	int px;
//     int py;
//     unsigned int color_c;
//     px = (v->player.view_x * v->tile_size ) - (int)v->t_cam.x;
// 	py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y;
//     color_c = get_pixel(&v->tx.player, x, y);    
// 	if (color_c != 0x000000 )
// 		put_pixel(v->frame.image, px + x, py + y, color_c);
// }

void draw_pixel_player(t_vars *v, int x, int y)
{
    int px;
    int py;
    uint32_t color_c;

    // Initialisation
    color_c = 0;

    px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
    if (v->player.jump == 1)
        py = (v->player.view_jump * v->tile_size) - (int)v->t_cam.y;
    else
        py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y;

    // Vérification des bornes
    if (x < 0 || x >= v->tile_size || y < 0 || y >= v->tile_size)
	{
		printf("return x ou y < 0 player\n");
        return;
	}
    // Limiter la frame à 0-5
    int frame = (int)(v->opt_txt.index_p);
    if (frame < 0)
        frame = 0;
    if (frame > 5)
        frame = 5;

    if (v->player.jump && v->input.left == 1)
        color_c = v->opt_txt.jump[y * v->tile_size + x];
    else if (v->player.jump)
        color_c = v->opt_txt.jump_r[y * v->tile_size + x];
    else if (v->input.left == 1)
        color_c = v->opt_txt.player[frame][y * v->tile_size + x];
    else if (v->input.right == 1)
        color_c = v->opt_txt.p_right[frame][y * v->tile_size + x];
    else
        color_c = v->opt_txt.placeholder[y * v->tile_size + x];
    if (color_c != 0x000000)
        put_pixel(&v->frame, px + x, py + y, color_c);
}	

void draw_pixel_shadow(t_vars *v, int x, int y)
{
	int	px;
	int	py;
	uint32_t color_c;

	px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
	py = ((v->player.view_y) * v->tile_size) - (int)v->t_cam.y;
	color_c = v->opt_txt.shadow[y * v->tile_size + x];

	if (color_c != 0x000000)
		put_pixel(&v->frame, px + x, py + y, color_c);
}
