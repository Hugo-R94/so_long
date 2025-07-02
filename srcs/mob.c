/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:35:39 by hugz              #+#    #+#             */
/*   Updated: 2025/07/02 15:18:47 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_ennemy(t_mob *mob, int x, int y)
{
	mob->mx = x;
	mob->my = y;
	mob->view_x = x ;
	mob->view_y = y;
	mob->vis = 1;
}

void	nb_mob(t_vars *v)
{
	int	x;
	int	y;
	int	mob_nb;

	x = 0;
	mob_nb = 0;
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
	int	y;
	int	x;
	int	i;

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

void	draw_pixel_mob(t_vars *v, int px, int py)
{
	int	bounds[4];
	int	pos[2];
	int	i;

	bounds[0] = v->player.grid_y - 3;
	bounds[1] = v->player.grid_y + 3;
	bounds[2] = v->player.grid_x - 6;
	bounds[3] = v->player.grid_x + 6;
	if (bounds[0] < 0)
		bounds[0] = 0;
	if (bounds[1] >= v->t_map.map_rows)
		bounds[1] = v->t_map.map_rows - 1;
	if (bounds[2] < 0)
		bounds[2] = 0;
	if (bounds[3] >= v->t_map.map_cols)
		bounds[3] = v->t_map.map_cols - 1;
	pos[0] = px;
	pos[1] = py;
	i = 0;
	while (i < v->nb_mob)
	{
		handle_draw_mob(v, i, bounds, pos);
		i++;
	}
}

void	handle_draw_mob(t_vars *v, int i, int *b, int *pos)
{
	int				mx;
	int				my;
	unsigned int	color;
	int				dx;
	int				dy;

	mx = v->mob[i].mx;
	my = v->mob[i].my;
	if (mx < b[2] || mx > b[3] || my < b[0] || my > b[1])
		return ;
	if (v->mob[i].vis == 1)
	{
		dx = (int)(v->mob[i].view_x * v->tile_size) - v->t_cam.x + pos[0];
		dy = (int)(v->mob[i].view_y * v->tile_size) - v->t_cam.y + pos[1];
		if (pos[0] < v->tile_size && pos[1] < v->tile_size
			&& dx >= 0 && dy >= 0)
		{
			color = v->opt_txt.mob[pos[1] * v->tile_size + pos[0]];
			if (color != 0x000000)
				put_pixel(&v->frame, dx, dy, color);
		}
	}
}
