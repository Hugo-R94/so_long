/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/01 17:15:29 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

static void update_player_velocity(t_vars *v)
{
    double accel = 0.02;
    double friction = 0.85;

    if (v->input.left)  v->player.vel_x -= accel;
    if (v->input.right) v->player.vel_x += accel;
    if (v->input.up)    v->player.vel_y -= accel;
    if (v->input.down)  v->player.vel_y += accel;

    v->player.vel_x *= friction;
    v->player.vel_y *= friction;
    move_player(v, v->player.vel_x, v->player.vel_y);
}

static void handle_coin_collection(t_vars *v)
{
    int i = 0;
    while (i < v->coin_count)
    {
        if (v->player.grid_x == v->coin[i].cx &&
            v->player.grid_y == v->coin[i].cy &&
            v->coin[i].vis == 1)
        {
            v->coin_get++;
            v->coin[i].vis = 0;
            //printf("Coin #%d ramassé, total: %d/%d\n", i, v->coin_get, v->coin_count);
        }
        i++;
    }
}

static void check_mob_collisions(t_vars *v)
{
    int y = 0;
    while (y < v->nb_mob)
    {
        if (v->mob[y].vis == 0)
        {
            y++;
            continue;
        }
        if (v->player.grid_x == (int)v->mob[y].mx &&
            v->player.grid_y == (int)v->mob[y].my)
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
                exit(EXIT_FAILURE);
        }
        y++;
    }
}

static void handle_jump_and_animation(t_vars *v)
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

static void handle_exit_check(t_vars *v)
{
    if (v->coin_get >= v->coin_count)
        v->exit.open = 1;

    if (v->player.grid_x == v->exit.ex &&
        v->player.grid_y == v->exit.ey &&
        v->exit.open == 1)
    {
        exit(EXIT_SUCCESS);
    }
}

int	game_loop(void *param)
{
	t_vars *v = (t_vars *)param;
	struct timeval start, end;
	long elapsed_us;
	const long frame_time_us = 33333;

	gettimeofday(&start, NULL);
	update_player_velocity(v);
	handle_coin_collection(v);
	mouv_mob_simple(v);
	check_mob_collisions(v);
	handle_exit_check(v);
	handle_jump_and_animation(v);
	update_camera(v);
	render_frame(v);
	gettimeofday(&end, NULL);
	if (v->input.down == 1 || v->input.up == 1|| v->input.left  == 1|| v->input.right ==1 )
		v->mouv_counter =  v->mouv_counter + 1;
	elapsed_us = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
	v->fps = 1000000 / elapsed_us;
	if (v->fps > 30)
		usleep(frame_time_us - elapsed_us);
	return (0); 
}
