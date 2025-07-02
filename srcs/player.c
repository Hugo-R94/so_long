/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 15:28:13 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_player(t_vars *v)
{
	v->player.vel_x = 0;
	v->player.vel_y = 0;
	v->player.jump = 0;
	v->player.jump_counter = 0;
	v->input.left = 0;
	v->input.right = 0;
	v->input.up = 0;
	v->input.down = 0;
	v->opt_txt.index_p = 0;
	v->mouv_counter = 0;
}

void	get_player_grid_pos(t_vars *v)
{
	int	y;
	int	x;

	y = 0;
	while (v->t_map.map[y])
	{
		x = 0;
		while (v->t_map.map[y][x])
		{
			if (v->t_map.map[y][x] == 'P')
			{
				v->player.grid_x = x;
				v->player.grid_y = y;
				v->player.view_x = (double)x;
				v->player.view_y = (double)y;
				v->player.view_jump = (double)y;
				init_player(v);
				return ;
			}
			x++;
		}
		y++;
	}
}

static uint32_t	put_color_player(t_vars *v, int x, int y, int frame)
{
	if (v->player.jump && v->input.left == 1)
		return (v->opt_txt.jump[y * v->tile_size + x]);
	else if (v->player.jump)
		return (v->opt_txt.jump_r[y * v->tile_size + x]);
	else if (v->input.left == 1)
		return (v->opt_txt.player[frame][y * v->tile_size + x]);
	else if (v->input.right == 1)
		return (v->opt_txt.p_right[frame][y * v->tile_size + x]);
	else
		return (v->opt_txt.placeholder[y * v->tile_size + x]);
}

void	draw_pixel_player(t_vars *v, int x, int y)
{
	int			px;
	int			py;
	uint32_t	color_c;
	int			frame;

	px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
	if (v->player.jump == 1)
		py = (v->player.view_jump * v->tile_size) - (int)v->t_cam.y;
	else
		py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y;
	if (x < 0 || x >= v->tile_size || y < 0 || y >= v->tile_size)
		return ;
	frame = (int)(v->opt_txt.index_p);
	if (frame < 0)
		frame = 0;
	if (frame > 5)
		frame = 5;
	color_c = put_color_player(v, x, y, frame);
	if (color_c != 0x000000)
		put_pixel(&v->frame, px + x, py + y, color_c);
}	

void	draw_pixel_shadow(t_vars *v, int x, int y)
{
	int			px;
	int			py;
	uint32_t	color_c;

	px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
	py = ((v->player.view_y) * v->tile_size) - (int)v->t_cam.y;
	color_c = v->opt_txt.shadow[y * v->tile_size + x];
	if (color_c != 0x000000)
		put_pixel(&v->frame, px + x, py + y, color_c);
}
