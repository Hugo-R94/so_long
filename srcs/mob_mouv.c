/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_mouv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:33:08 by hugz              #+#    #+#             */
/*   Updated: 2025/07/02 15:03:40 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_mob_width(t_vars *v, t_mob *mob)
{
	int	lx;
	int	ly;
	int	width;

	width = 0;
	lx = mob->mx;
	ly = mob->my;
	while (lx >= 0 && !is_wall(v->t_map.map[ly][lx]))
		lx--;
	lx++;
	while (lx < v->t_map.map_cols && !is_wall(v->t_map.map[ly][lx]))
	{
		lx++;
		width++;
	}
	return (width);
}

int	get_mob_height(t_vars *v, t_mob *mob)
{
	int	lx;
	int	ly;
	int	height;

	lx = mob->mx;
	ly = mob->my;
	height = 0;
	while (ly >= 0 && !is_wall(v->t_map.map[ly][lx]))
		ly--;
	ly++;
	while (ly < v->t_map.map_rows && !is_wall(v->t_map.map[ly][lx]))
	{
		ly++;
		height++;
	}
	return (height);
}

void	set_mouv_axis(t_vars *v, t_mob *mob)
{
	int	width;
	int	height;

	width = get_mob_width(v, mob);
	height = get_mob_height(v, mob);
	if (height >= width)
		mob->axis = 'y';
	else
		mob->axis = 'x';
}

void	mouv_mob_x_update(t_vars *v, t_mob *mob, int new_view_x, int new_mx)
{
	if (is_wall(v->t_map.map[new_mx][mob->my]))
		mob->dir = -mob->dir;
	else
	{
		mob->mx = new_mx;
		mob->view_x = new_view_x;
	}
}

void	mouv_mob_x(t_vars *v, t_mob *mob)
{
	int	new_view_x;
	int	new_mx;

	new_view_x = mob->view_x + mob->dir;
	new_mx = mob->mx;
	if (mob->dir > 0)
	{
		if (new_view_x >= (mob->mx + 1) * v->tile_size)
		{
			new_mx = mob->mx + 1;
			mouv_mob_x_update(v, mob, new_view_x, new_mx);
		}
		else
			mob->view_x = new_view_x;
	}
	else if (mob->dir < 0)
	{
		if (new_view_x < mob->mx * v->tile_size)
		{
			new_mx = mob->mx - 1;
			mouv_mob_x_update(v, mob, new_view_x, new_mx);
		}
		else
			mob->view_x = new_view_x;
	}
}
