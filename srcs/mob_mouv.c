/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_mouv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:33:08 by hugz              #+#    #+#             */
/*   Updated: 2025/06/24 14:50:42 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void set_mouv_axis(t_vars *v, t_mob *mob)
{
	int lx;
	int ly;
	int height;
	int width;

	height = 0;
	width = 0;
	lx = mob->mx;
	ly = mob->my;
	while (lx >= 0 && !is_wall(v->t_map.map[ly][lx]))
		lx--;
	lx++; // Revenir à la dernière position non mur
	while (lx < v->t_map.map_cols && !is_wall(v->t_map.map[ly][lx]))
	{
		lx++;
		width++;
	}
	lx = mob->mx;
	ly = mob->my;
	while (ly >= 0 && !is_wall(v->t_map.map[ly][lx]))
		ly--;
	ly++; // Revenir à la dernière position non mur
	while (ly < v->t_map.map_rows && !is_wall(v->t_map.map[ly][lx]))
	{
		ly++;
		height++;
	}
	if (height >= width)
		mob->axis = 'y';
	else
		mob->axis = 'x';
}


static void mouv_mob_x(t_vars *v, t_mob *mob)
{
	int new_view_x;
	int new_mx;

	new_view_x = mob->view_x + mob->dir;
	new_mx = mob->mx;
	if (mob->dir > 0)
	{
		if (new_view_x >= (mob->mx + 1) * v->tile_size)
		{
			new_mx = mob->mx + 1;
			if (is_wall(v->t_map.map[new_mx][mob->my]))
				mob->dir = -mob->dir;
			else
			{
				mob->mx = new_mx;
				mob->view_x = new_view_x;
			}
		}
		else
			mob->view_x = new_view_x;
	}
	else if (mob->dir < 0)
	{
		if (new_view_x < mob->mx * v->tile_size)
		{
			new_mx = mob->mx - 1;
			if (is_wall(v->t_map.map[new_mx][mob->my]))
				mob->dir = -mob->dir;
			else
			{
				mob->mx = new_mx;
				mob->view_x = new_view_x;
			}
		}
		else
			mob->view_x = new_view_x;
	}
}

static void mouv_mob_y(t_vars *v, t_mob *mob)
{
	int new_view_y;
	int new_my;

	new_view_y = mob->view_y + mob->dir;
	new_my = mob->my;
	if (mob->dir > 0)
	{
		if (new_view_y >= (mob->my + 1) * v->tile_size)
		{
			new_my = mob->my + 1;
			if (is_wall(v->t_map.map[mob->mx][new_my]))
				mob->dir = -mob->dir;
			else
			{
				mob->my = new_my;
				mob->view_y = new_view_y;
			}
		}
		else
			mob->view_y = new_view_y;
	}
	else if (mob->dir < 0)
	{
		if (new_view_y < mob->my * v->tile_size)
		{
			new_my = mob->my - 1;
			if (is_wall(v->t_map.map[mob->mx][new_my]))
				mob->dir = -mob->dir;
			else
			{
				mob->my = new_my;
				mob->view_y = new_view_y;
			}
		}
		else
			mob->view_y = new_view_y;
	}
}

void mouv_all_mob(t_vars *v)
{
	int i;

	i = 0;
	while (i < v->nb_mob)
	{
		if (v->mob[i].axis == 'x')
			mouv_mob_x(v, &v->mob[i]);
		else if (v->mob[i].axis == 'y')
			mouv_mob_y(v, &v->mob[i]);
		i++;
	}
}
void mouv_mob_simple(t_vars *v)
{
	int i;
	float next_x;
	float next_y;
	int check_x;
	int check_y;

	i = 0;
	while (i < v->nb_mob)
	{
		next_x = v->mob[i].view_x;
		next_y = v->mob[i].view_y;

		if (v->mob[i].axis == 'x')
			next_x = next_x + (0.05f * v->mob[i].dir);
		else if (v->mob[i].axis == 'y')
			next_y = next_y + (0.05f * v->mob[i].dir);

		check_x = (int)(next_x + 0.5f);
		check_y = (int)(next_y + 0.5f);

		// Tester si la prochaine case est un mur
		if (is_wall(v->t_map.map[check_y][check_x]))
			v->mob[i].dir = v->mob[i].dir * -1;
		else
		{
			v->mob[i].view_x = next_x;
			v->mob[i].view_y = next_y;
		}
		v->mob[i].mx = v->mob[i].view_x + 0.5;
		v->mob[i].my = v->mob[i].view_y + 0.5;
		//printf("mob %d view_x = %f view_y = %f dir = %d\n", i, v->mob[i].view_x, v->mob[i].view_y, v->mob[i].dir);
		i++;
	}
}
