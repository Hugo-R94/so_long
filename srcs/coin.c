/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/04 11:15:56 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_coin_count(t_vars *vars)
{
	int	i;
	int	j;
	int	count;

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

void	load_coin(t_vars *vars)
{
	int	index;
	int	i;
	int	j;

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
	int				draw_x;
	int				draw_y;
	int				tile;
	unsigned int	color_c;

	tile = v->tile_size;
	draw_x = (v->coin[i].cx * tile) - (int)v->t_cam.x + x;
	draw_y = (v->coin[i].cy * tile) - (int)v->t_cam.y + y;
	color_c = v->opt_txt.coin[y * v->tile_size + x];
	if (color_c != 0x000000)
		put_pixel(&v->frame, draw_x, draw_y, color_c);
}

void	draw_pixel_coins(t_vars *v, int x, int y)
{
	int	top;
	int	bottom;
	int	le;
	int	ri;
	int	i;

	top = (int)v->player.view_y - 3;
	bottom = v->player.grid_y + 3;
	le = v->player.grid_x - 6;
	ri = v->player.grid_x + 6;
	if (top < 0)
		top = 0;
	if (bottom >= v->t_map.map_rows)
		bottom = v->t_map.map_rows - 1;
	if (le < 0)
		le = 0;
	if (ri >= v->t_map.map_cols)
		ri = v->t_map.map_cols - 1;
	i = -1;
	while (++i < v->coin_count)
		if (v->coin[i].cx >= le && v->coin[i].cx <= ri && v->coin[i].cy >= top
			&& v->coin[i].cy <= bottom && v->coin[i].vis)
			draw_single_coin(v, i, x, y);
}
