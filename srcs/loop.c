/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/20 18:39:40 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <sys/time.h>

#include "so_long.h"
#include <sys/time.h>
#include <unistd.h>  // pour usleep
#include <stdio.h>   // pour printf

void	game_loop(t_vars *v)
{
	struct timeval start, end;
	long elapsed_us;
	const long frame_time_us = 33333; // ~16.666 ms pour 60 FPS

	gettimeofday(&start, NULL);

	// --- logique du jeu ---
	double accel = 0.02;
	double friction = 0.85;
	int i;

	if (v->input.left)  v->player.vel_x -= accel;
	if (v->input.right) v->player.vel_x += accel;
	if (v->input.up)    v->player.vel_y -= accel;
	if (v->input.down)  v->player.vel_y += accel;

	v->player.vel_x *= friction;
	v->player.vel_y *= friction;
	move_player(v, v->player.vel_x, v->player.vel_y);

	for (i = 0; i < v->coin_count; i++)
	{
		if (v->player.grid_x == v->coin[i].cx &&
			v->player.grid_y == v->coin[i].cy &&
			v->coin[i].vis == 1)
		{
			v->coin[i].vis = 0;
			v->coin_get++;
		}
	}

	if (v->coin_get == v->coin_count)
		v->exit.open = 1;

	if (v->player.grid_x == v->exit.ex &&
		v->player.grid_y == v->exit.ey &&
		v->exit.open == 1)
	{
		printf("VICTOIRE !!\n");
		exit(EXIT_SUCCESS);
	}

	update_camera(v);
	render_frame(v);

	gettimeofday(&end, NULL);
	elapsed_us = (end.tv_sec - start.tv_sec) * 1000000L
	           + (end.tv_usec - start.tv_usec);

	// Calcul et affichage des FPS
	double fps = 1000000.0 / (double)elapsed_us;
	printf("FPS: %.2f (frame time: %ld µs)\n", fps, elapsed_us);

	// Limiter à ~60 FPS
	if (elapsed_us < frame_time_us)
		usleep(frame_time_us - elapsed_us);
}
