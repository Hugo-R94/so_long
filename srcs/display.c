/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:44:17 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/17 18:23:02 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void update_camera(t_vars *v)
{
    double target_x = v->player.view_x;
    double target_y = v->player.view_y;
	int max_offset;
	
	max_offset = 800;
    // Interpolation vers la cible avec un "retard"
    v->t_cam.x = v->player.view_x * v->tile_size - RES_X / 2;
    v->t_cam.y = v->player.view_y * v->tile_size - RES_Y / 2;
	
    // Bordures à ne pas dépasser
    int map_px_width = v->t_map.map_cols * v->tile_size;
    int map_px_height = v->t_map.map_rows * v->tile_size;
	
	printf("player x = %f | player y = %f\n",v->t_cam.x,v->t_cam.y);
}


void init_camera(t_vars *v)
{
	v->t_cam.x = v->player.view_x;
	v->t_cam.y = v->player.view_y;
	v->t_cam.speed = 0.2;

	int total_map_width = v->t_map.map_cols * v->tile_size;
	int total_map_height = v->t_map.map_rows * v->tile_size;

	// Limites pour ne pas dépasser de plus de 600 px du bord
	v->t_cam.limit_left = 600;
	v->t_cam.limit_right = total_map_width - RES_X + 600;
	v->t_cam.limit_top = 600;
	v->t_cam.limit_bottom = total_map_height - RES_Y + 600;
}


void render_frame(t_vars *v)
{
    int i = 0;
    mlx_clear_window(v->mlx, v->win);

 

    render_background(v);
	while (i < v->coin_count)
    		render_coin(v, &v->coin[i++]);
    render_player(v);
}
