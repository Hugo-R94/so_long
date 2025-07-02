/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_mouv1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:01:45 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 15:04:40 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mouv_mob_y_update(t_vars *v, t_mob *mob, int new_view_y, int new_my)
{
	if (is_wall(v->t_map.map[mob->mx][new_my]))
		mob->dir = -mob->dir;
	else
	{
		mob->my = new_my;
		mob->view_y = new_view_y;
	}
}

void	mouv_mob_y(t_vars *v, t_mob *mob)
{
	int	new_view_y;
	int	new_my;

	new_view_y = mob->view_y + mob->dir;
	new_my = mob->my;
	if (mob->dir > 0)
	{
		if (new_view_y >= (mob->my + 1) * v->tile_size)
		{
			new_my = mob->my + 1;
			mouv_mob_y_update(v, mob, new_view_y, new_my);
		}
		else
			mob->view_y = new_view_y;
	}
	else if (mob->dir < 0)
	{
		if (new_view_y < mob->my * v->tile_size)
		{
			new_my = mob->my - 1;
			mouv_mob_y_update(v, mob, new_view_y, new_my);
		}
		else
			mob->view_y = new_view_y;
	}
}

void	mouv_all_mob_one(t_vars *v, int i)
{
	if (v->mob[i].axis == 'x')
		mouv_mob_x(v, &v->mob[i]);
	else if (v->mob[i].axis == 'y')
		mouv_mob_y(v, &v->mob[i]);
}

void	mouv_all_mob(t_vars *v)
{
	int	i;

	i = 0;
	while (i < v->nb_mob)
	{
		mouv_all_mob_one(v, i);
		i++;
	}
}

void	mouv_mob_simple_one(t_vars *v, int i)
{
	float	next_x;
	float	next_y;
	int		check_x;
	int		check_y;

	next_x = v->mob[i].view_x;
	next_y = v->mob[i].view_y;
	if (v->mob[i].axis == 'x')
		next_x = next_x + (0.05f * v->mob[i].dir);
	else if (v->mob[i].axis == 'y')
		next_y = next_y + (0.05f * v->mob[i].dir);
	check_x = (int)(next_x + 0.5f);
	check_y = (int)(next_y + 0.5f);
	if (is_wall(v->t_map.map[check_y][check_x]))
		v->mob[i].dir = v->mob[i].dir * -1;
	else
	{
		v->mob[i].view_x = next_x;
		v->mob[i].view_y = next_y;
	}
	v->mob[i].mx = v->mob[i].view_x + 0.5;
	v->mob[i].my = v->mob[i].view_y + 0.5;
}
