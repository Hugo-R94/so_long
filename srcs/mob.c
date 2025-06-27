/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:35:39 by hugz              #+#    #+#             */
/*   Updated: 2025/06/27 12:46:35 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_ennemy(t_mob *mob, int x, int y)
{
	mob->mx = x;
	mob->my = y;
	mob->view_x = x ;
	mob->view_y = y;
	mob->vis = 1;
}


void	nb_mob(t_vars *v)
{
	int x = 0;
	int y;
	int mob_nb = 0;

	while (v->t_map.map[x])
	{
		y = 0;
		while (v->t_map.map[x][y])
		{
			if (v->t_map.map[x][y] == 'M')
				mob_nb++;
			y++;
		}
		x++;
	}
	v->nb_mob = mob_nb;
}


void	set_all_ennemy(t_vars *v)
{
	int y;
	int x;
	int i;

	i = 0;
	y = 0;
	v->mob = malloc(sizeof(t_mob) * v->nb_mob);
	while (v->t_map.map[y])
	{
		x = 0;
		while (v->t_map.map[y][x])
		{
			if (v->t_map.map[y][x] == 'M')
			{
				set_ennemy(&v->mob[i], x, y);
				set_mouv_axis(v, &v->mob[i]); 
				v->mob[i].dir = 1;
				i++;
			}
			x++;
		}
		y++;
	}
}


// void draw_pixel_mob(t_vars *v, int px, int py)
// {
// 	int top = v->player.grid_y - 3;
// 	int bottom = v->player.grid_y + 3;
// 	int left = v->player.grid_x - 6;
// 	int right = v->player.grid_x + 6;

// 	if (top < 0) top = 0;
// 	if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
// 	if (left < 0) left = 0;
// 	if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;

// 	int i = 0;
// 	while (i < v->nb_mob)
// 	{
// 		int mx = v->mob[i].mx;  // grille
// 		int my = v->mob[i].my;  // grille
// 		if (mx < left || mx > right || my < top || my > bottom)
// 		{
// 			i++;
// 			continue;
// 		}
// 		if (v->mob[i].vis == 1)
// 		{
// 			int draw_x = (int)(v->mob[i].view_x * v->tile_size) - v->t_cam.x + px;
// 			int draw_y = (int)(v->mob[i].view_y * v->tile_size) - v->t_cam.y + py;

// 			if (px < v->tile_size && py < v->tile_size)
// 			{
// 				unsigned int color = v->opt_txt.mob[py * v->tile_size + px];
// 				if (color != 0x000000)
// 					put_pixel(&v->frame, draw_x, draw_y, color);
// 			}
// 		}
// 		i++;
// 	}
// }

void draw_pixel_mob(t_vars *v, int px, int py)
{
	int top = v->player.grid_y - 3;
	int bottom = v->player.grid_y + 3;
	int left = v->player.grid_x - 6;
	int right = v->player.grid_x + 6;

	if (top < 0) top = 0;
	if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
	if (left < 0) left = 0;
	if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;

	int i = 0;
	while (i < v->nb_mob)
	{
		handle_draw_mob(v, i, px, py, top, bottom, left, right);
		i++;
	}
}
void handle_draw_mob(t_vars *v, int i, int px, int py, int top, int bottom, int left, int right)
{
	int mx = v->mob[i].mx;
	int my = v->mob[i].my;

	if (mx < left || mx > right || my < top || my > bottom)
		return;

	if (v->mob[i].vis == 1)
	{
		int draw_x = (int)(v->mob[i].view_x * v->tile_size) - v->t_cam.x + px;
		int draw_y = (int)(v->mob[i].view_y * v->tile_size) - v->t_cam.y + py;
		if (px < v->tile_size && py < v->tile_size && draw_x >= 0 && draw_y >= 0)
		{
			unsigned int color = v->opt_txt.mob[py * v->tile_size + px];
			if (color != 0x000000)
				put_pixel(&v->frame, draw_x, draw_y, color);
		}
	}
}
