/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/24 18:05:15 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
				return;
			}
			x++;
		}
		y++;
	}
}

void draw_player(t_vars *v)
{
    int px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
    int py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y;

    if (!v->tx.player.image || !v->tx.player.data)
    {
        ft_printf("player texture NULL dans render_player\n");
        return;
    }
    draw_image(&v->frame, &v->tx.player, px, py);
}

void	draw_shadow(t_vars *v)
{
	 int px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
   	 int py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y ;
	 draw_image(&v->frame, &v->tx.shadow, px, py);
}
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
    unsigned int color_c;
    px = (v->player.view_x * v->tile_size ) - (int)v->t_cam.x;
	if (v->player.jump)
		py = (v->player.view_jump * v->tile_size) - (int)v->t_cam.y;
	else
		py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y;
    color_c = v->opt_txt.player[y * v->tile_size + x];    
	if (color_c != 0x000000 )
		put_pixel(v->frame.image, px + x, py + y, color_c);
}

void draw_pixel_shadow(t_vars *v, int x, int y)
{
	int	px;
	int	py;
	float offset = 0.0;
	unsigned int color_c;

	px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;

	// Si le joueur saute, on applique un offset à l'ombre
	// if (v->player.jump)
	// {
	// 	if (v->player.jump_counter < 7)
	// 		offset = v->player.jump_counter * 0.15;
	// 	else
	// 		offset = (14 - v->player.jump_counter) * 0.15;
	// }

	py = ((v->player.view_y + offset) * v->tile_size) - (int)v->t_cam.y;

	color_c = v->opt_txt.shadow[y * v->tile_size + x];

	if (color_c != 0x000000)
		put_pixel(v->frame.image, px + x, py + y, color_c);
}
