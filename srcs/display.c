/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:44:17 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/18 16:01:03 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void update_camera(t_vars *v)
{
    // Coordonnées cibles = centrer le joueur
    double target_x = v->player.view_x * v->tile_size - RES_X / 2;
    double target_y = v->player.view_y * v->tile_size - RES_Y / 2;

    // Lerp (interpolation linéaire)
    double lerp_factor = 0.08; // 0.0 = aucun mouvement, 1.0 = instantané

    v->t_cam.x += (target_x - v->t_cam.x) * lerp_factor;
    v->t_cam.y += (target_y - v->t_cam.y) * lerp_factor;

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
