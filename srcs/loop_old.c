/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/26 18:07:54 by hrouchy          ###   ########.fr       */
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
	const long frame_time_us = 33333;

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
	i = 0;
	while (i < v->coin_count)
	{
		if (v->player.grid_x == v->coin[i].cx &&
			v->player.grid_y == v->coin[i].cy &&
			v->coin[i].vis == 1)
		{
			
			v->coin_get++;
			v->coin[i].vis = 0;
			printf("Coin #%d ramassé, total: %d/%d\n", i, v->coin_get, v->coin_count);
		}
		i++;
	}
	mouv_mob_simple(v);
	int y = 0;
	

	while (y < v->nb_mob)
{
	if (v->mob[y].vis == 0)
	{
		y++;
		continue;
	}
	if (v->player.grid_x == (int)v->mob[y].mx 
		&& v->player.grid_y == (int)v->mob[y].my 
		&& v->mob[y].vis == 1)
	{
		if (v->player.jump == 1)
		{
			v->mob[y].vis = 0;

			double rebound_strength = 1.0 - ((double)v->player.jump_counter / 25.0);
			if (rebound_strength < 0.1)
				rebound_strength = 0.1;

			v->player.view_jump -= rebound_strength * 0.5;
		}

		else
		{
			printf("player x = %i player y = %i | mob x = %i mpb y = %i\n",v->player.grid_x,v->player.grid_x,v->mob[y].mx,v->mob[y].my);
			printf("c'est loose ...... \n");
			exit(EXIT_FAILURE);
		}
	}

	y++; // toujours incrémenter y !
}

	//printf("mob[0]x = %i | mob[0]y = %i \nplayerx = %i | playery = %i\n", v->mob[0].mx, v->mob[0].my, v->player.grid_x,v->player.grid_y);	

	
if (v->coin_get >= v->coin_count)
	{
		v->exit.open = 1;
		//printf(" player pos x = %i y = %i | exit pos x = %i y = %i\n",v->player.grid_x,v->player.grid_y,v->exit.ex,v->exit.ey);
		//printf("EXIT OPEN\n");
	}
	if (v->player.grid_x == v->exit.ex &&
		v->player.grid_y == v->exit.ey &&
		v->exit.open == 1)
		//printf("player sur sortie \n");
	if (v->player.grid_x == v->exit.ex &&
		v->player.grid_y == v->exit.ey &&
		v->exit.open == 1)
	{
		printf("VICTOIRE !!\n");
		exit(EXIT_SUCCESS);
	}
	
	if (v->input.left || v->input.right) {
   		v->opt_txt.index_p += 0.33;
    if (v->opt_txt.index_p > 5)
        v->opt_txt.index_p = 0;
	} else {
		v->opt_txt.index_p = 0; // idle frame si aucune touche
	}
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
	
	//printf("%i | %i\n",v->coin_count, v->coin_get);
	update_camera(v);
	
	render_frame(v);

	gettimeofday(&end, NULL);
	elapsed_us = (end.tv_sec - start.tv_sec) * 1000000L
	           + (end.tv_usec - start.tv_usec);


	int fps = 1000000.0 / elapsed_us;
	// if (fps < 30)
	// 	printf("FPS: %i \n", fps);
	// else
	// 	printf("FPS: 30\n");
	//printf("FPS: %i \n", fps);

	if (elapsed_us < frame_time_us)
		usleep(frame_time_us - elapsed_us);
}
