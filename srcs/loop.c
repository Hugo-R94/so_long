/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/03 11:26:33 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

void	update_player_velocity(t_vars *v)
{
	double	accel;
	double	friction;

	accel = 0.022;
	friction = 0.85;
	if (v->input.left)
		v->player.vel_x -= accel;
	if (v->input.right)
		v->player.vel_x += accel;
	if (v->input.up)
		v->player.vel_y -= accel;
	if (v->input.down)
		v->player.vel_y += accel;
	v->player.vel_x *= friction;
	v->player.vel_y *= friction;
	move_player(v, v->player.vel_x, v->player.vel_y);
}

void	handle_coin_collection(t_vars *v)
{
	int	i;

	i = 0;
	while (i < v->coin_count)
	{
		if (v->player.grid_x == v->coin[i].cx
			&& v->player.grid_y == v->coin[i].cy
			&& v->coin[i].vis == 1)
		{
			v->coin_get++;
			v->coin[i].vis = 0;
		}
		i++;
	}
}

void	check_mob_collisions(t_vars *v)
{
	int		y;
	double	rebound_strength;

	y = -1;
	while (++y < v->nb_mob)
	{
		if (v->mob[y].vis == 0)
			continue ;
		if (v->player.grid_x == (int)v->mob[y].mx
			&& v->player.grid_y == (int)v->mob[y].my)
		{
			if (v->player.jump == 1)
			{
				v->mob[y].vis = 0;
				rebound_strength = 1 - ((double)v->player.jump_counter / 25.0);
				if (rebound_strength < 0.1)
					rebound_strength = 0.1;
				v->player.view_jump -= rebound_strength * 0.5;
			}
			else
				exit(EXIT_FAILURE);
		}
	}
}

void	handle_jump_and_animation(t_vars *v)
{
	if (v->input.left || v->input.right)
	{
		v->opt_txt.index_p += 0.33;
		if (v->opt_txt.index_p > 5)
			v->opt_txt.index_p = 0;
	}
	else
		v->opt_txt.index_p = 0;
	if (v->player.jump)
	{
		if (v->player.jump_counter < 7)
			v->player.view_jump -= 0.1;
		else if (v->player.jump_counter < 14)
			v->player.view_jump += 0.1;
		else
		{
			v->player.jump = 0;
			v->player.jump_counter = 0;
		}
		v->player.jump_counter++;
	}
}

void	handle_exit_check(t_vars *v)
{
	if (v->coin_get >= v->coin_count)
		v->exit.open = 1;
	if (v->player.grid_x == v->exit.ex
		&& v->player.grid_y == v->exit.ey
		&& v->exit.open == 1)
	{
		clean_and_exit(v);
	}
}
