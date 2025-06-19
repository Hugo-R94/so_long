/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/19 14:59:55 by hrouchy          ###   ########.fr       */
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

	printf("px = %i | py = %i\n",px,py);
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
