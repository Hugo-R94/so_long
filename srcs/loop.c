/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/19 16:33:02 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_loop(t_vars *v)
{
	double	accel = 0.02;
	double	friction = 0.85;
	int		i;

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
	i = 0;
	while (i < v->coin_count)
	{
		if (v->player.grid_x == v->coin[i].cx && v->player.grid_y == v->coin[i].cy && v->coin[i].vis == 1)
		{
			v->coin[i].vis = 0;
			v->coin_get++;
		}
		i++;
	}
	if (v->coin_get == v->coin_count)
		v->exit.open = 1;
	if (v->player.grid_x == v->exit.ex && v->player.grid_y == v->exit.ey && v->exit.open == 1)
	{
		printf("VICTOIRE !!\n");
		exit(EXIT_SUCCESS);
	}
	
	update_camera(v);
	render_frame(v);
	usleep(500);
	return ;
}