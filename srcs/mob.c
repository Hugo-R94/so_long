/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:35:39 by hugz              #+#    #+#             */
/*   Updated: 2025/06/24 14:41:14 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_ennemy(t_vars *v, t_mob *mob, int x, int y)
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
				set_ennemy(v, &v->mob[i], x, y);
				set_mouv_axis(v, &v->mob[i]); 
				v->mob[i].dir = 1;
				// printf("mouv axis mob n%i = %i\n",i,v->mob[i].dir);
				// printf("mob n*%i x = %i | y = %i\n", i, v->mob[i].mx, v->mob[i].my);
				i++;
			}
			x++;
		}
		y++;
	}
}


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
		int mx = v->mob[i].mx;  // grille
		int my = v->mob[i].my;  // grille

		// Check si mob dans la zone visible de la grille
		if (mx < left || mx > right || my < top || my > bottom)
		{
			i++;
			continue;
		}
		if (v->mob[i].vis == 1)
		{
			int draw_x = (int)(v->mob[i].view_x * v->tile_size) - v->t_cam.x + px;
			int draw_y = (int)(v->mob[i].view_y * v->tile_size) - v->t_cam.y + py;

			if (px < v->tile_size && py < v->tile_size)
			{
				unsigned int color = v->opt_txt.mob[py * v->tile_size + px];
				if (color != 0x000000)
					put_pixel(&v->frame, draw_x, draw_y, color);
			}
		}
		i++;
	}
}


// void draw_pixel_coins(t_vars *v, int x, int y)
// {
//     int top = (int)v->player.view_y  - 3;
//     int bottom = (int)v->player.grid_y + 3;
//     int left = (int)v->player.grid_x - 6;
//     int right = (int)v->player.grid_x + 6;

//     if (top < 0) top = 0;
//     if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
//     if (left < 0) left = 0;
//     if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;
    
//     for (int i = 0; i < v->nb_mob; i++)
//     {
//         int cx = v->coin[i].cx;
//         int cy = v->coin[i].cy;

//         // On ignore les pièces hors de la vue
//         if (cx < left || cx > right || cy < top || cy > bottom)
//             continue;

//         if (v->coin[i].vis == 1)
//         {
//             int draw_x = (cx * v->tile_size) - (int)v->t_cam.x + x;
//             int draw_y = (cy * v->tile_size) - (int)v->t_cam.y + y;
//             unsigned int color_c = v->opt_txt.coin[y * v->tile_size +x];

//             if (color_c != 0x000000)
//                 put_pixel(v->frame.image, draw_x, draw_y, color_c);
//         }
//     }
// }
