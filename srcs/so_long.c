/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:40:47 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/18 16:22:16 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	Loop_function(t_vars *v)
{
	mlx_hook(v->win, 2, 1L << 0, key_pressed_p, v);     // key down
	mlx_hook(v->win, 3, 1L << 1, key_release_p, v);   // key up
	mlx_loop_hook(v->mlx, game_loop, v);           // loop appelée à chaque "frame"
	mlx_loop(v->mlx);
}

void	init_level(t_vars *v)
{
	calculate_tile_size_n_mapsize(v);	
	calculate_offset(v);
	update_camera(v);
	get_player_grid_pos(v);
	get_exit(v);
	init_coins(v);
	init_texture(v);
}