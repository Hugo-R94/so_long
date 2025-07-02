/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:34:36 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 15:39:09 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	game_loop(t_vars *v)
{
	struct timeval	st;
	struct timeval	end;
	long			elapsed;
	long			frame_time_us;

	frame_time_us = 33333;
	gettimeofday(&st, NULL);
	update_player_velocity(v);
	handle_coin_collection(v);
	mouv_mob_simple(v);
	check_mob_collisions(v);
	handle_exit_check(v);
	handle_jump_and_animation(v);
	update_camera(v);
	render_frame(v);
	gettimeofday(&end, NULL);
	if (v->input.down == 1 || v->input.up == 1
		|| v->input.left == 1 || v->input.right == 1)
		v->mouv_counter = v->mouv_counter + 1;
	elapsed = (end.tv_sec - st.tv_sec) * 1000000L + (end.tv_usec - st.tv_usec);
	v->fps = 1000000 / elapsed;
	if (v->fps > 30)
		usleep(frame_time_us - elapsed);
	return (0);
}
