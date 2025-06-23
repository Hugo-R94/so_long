/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/20 12:27:27 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_coin_count(t_vars *vars)
{
	int i;
	int j;
	int count;
	
	i = 0;
	count = 0;
	while (vars->t_map.map[i])
	{
		j = 0;
		while (vars->t_map.map[i][j])
		{
			if (vars->t_map.map[i][j] == 'C')
				count++;
			j++;
		}
	i++;
	}
	vars->coin_count = count;
}

void load_coin(t_vars *vars)
{
    int index;
    int i;
    int j;

    vars->coin = malloc(sizeof(t_coin) * vars->coin_count);
    if (!vars->coin)
    {
        ft_printf("Erreur malloc coins\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    index = 0;
    while (vars->t_map.map[i])
    {
        j = 0;
        while (vars->t_map.map[i][j])
        {
            if (vars->t_map.map[i][j] == 'C')
            {
                vars->coin[index].cx = j; // colonne
                vars->coin[index].cy = i; // ligne
				vars->coin[index].vis = 1;
                index++;
            }
            j++;
        }
        i++;
    }
}

void	init_coins(t_vars *v)
{
	int i;
	
	i = 0;
	get_coin_count(v);
	load_coin(v);
	v->coin_get = 0;
}

void draw_coin(t_vars *v, int index)
{
    int cx = (v->coin[index].cx * v->tile_size ) - (int)v->t_cam.x;
	int cy = (v->coin[index].cy * v->tile_size) - (int)v->t_cam.y;
	if (v->coin[index].vis == 1)
   		draw_image(&v->frame, &v->tx.coin, cx, cy);
}

// void draw_pixel_coins(t_vars *v, int x, int y)
// {
// 	int cx;
//     int cy;
//     int i;
//     unsigned int color_c;
//     i = 0;
//     while(i < v->coin_count)
//     {
//          cx = (v->coin[i].cx * v->tile_size ) - (int)v->t_cam.x;
//          cy = (v->coin[i].cy * v->tile_size) - (int)v->t_cam.y;
//          color_c = get_pixel(&v->tx.coin, x, y);
//          if (v->coin[i].vis == 1 && color_c != 0x000000 )
// 			 	put_pixel(v->frame.image, cx + x , cy +y , color_c);
//         i++;
//     }
// }
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

//     for (int i = 0; i < v->coin_count; i++)
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
//             unsigned int color_c = get_pixel(&v->tx.coin, x, y);

//             if (color_c != 0x000000)
//                 put_pixel(v->frame.image, draw_x, draw_y, color_c);
//         }
//     }
// }
void draw_pixel_coins(t_vars *v, int x, int y)
{
    int top = (int)v->player.view_y  - 3;
    int bottom = (int)v->player.grid_y + 3;
    int left = (int)v->player.grid_x - 6;
    int right = (int)v->player.grid_x + 6;

    if (top < 0) top = 0;
    if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
    if (left < 0) left = 0;
    if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;

    for (int i = 0; i < v->coin_count; i++)
    {
        int cx = v->coin[i].cx;
        int cy = v->coin[i].cy;

        // On ignore les pièces hors de la vue
        if (cx < left || cx > right || cy < top || cy > bottom)
            continue;

        if (v->coin[i].vis == 1)
        {
            int draw_x = (cx * v->tile_size) - (int)v->t_cam.x + x;
            int draw_y = (cy * v->tile_size) - (int)v->t_cam.y + y;
            unsigned int color_c = v->opt_txt.coin[y * v->tile_size +x];

            if (color_c != 0x000000)
                put_pixel(v->frame.image, draw_x, draw_y, color_c);
        }
    }
}
