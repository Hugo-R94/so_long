/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/27 12:07:49 by hugz             ###   ########.fr       */
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
        exit(EXIT_FAILURE);
    i = 0;
    index = 0;
    while (vars->t_map.map[i])
    {
        j = 0;
        while (vars->t_map.map[i][j])
        {
            if (vars->t_map.map[i][j] == 'C')
            {
                vars->coin[index].cx = j;
                vars->coin[index].cy = i;
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
	
	get_coin_count(v);
	load_coin(v);
	v->coin_get = 0;
}

void	draw_single_coin(t_vars *v, int i, int x, int y)
{
	int		draw_x;
	int		draw_y;
	int		tile;

	tile = v->tile_size;
	draw_x = (v->coin[i].cx * tile) - (int)v->t_cam.x + x;
	draw_y = (v->coin[i].cy * tile) - (int)v->t_cam.y + y;
    unsigned int color_c = v->opt_txt.coin[y * v->tile_size +x];
	 if (color_c != 0x000000)
        put_pixel(&v->frame, draw_x, draw_y, color_c);
}
void	draw_pixel_coins(t_vars *v, int x, int y)
{
	int	top;
	int	bottom;
	int	left;
	int	right;
	int	i;

	top = (int)v->player.view_y - 3;
	bottom = v->player.grid_y + 3;
	left = v->player.grid_x - 6;
	right = v->player.grid_x + 6;
	if (top < 0) top = 0;
	if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
	if (left < 0) left = 0;
	if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;
	i = 0;
	while (i < v->coin_count)
	{
		int cx = v->coin[i].cx;
		int cy = v->coin[i].cy;
		if (cx >= left && cx <= right && cy >= top && cy <= bottom && v->coin[i].vis)
			draw_single_coin(v, i, x, y);
		i++;
	}
}
