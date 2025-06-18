/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:26:17 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/18 17:57:40 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

move_player(t_vars *vars, double dx, double dy)
{
	double	new_x;
	double	new_y;
	int		new_x_g;
	int		new_y_g;
	
	new_x = (vars->player.view_x) + dx;
	new_y = (vars->player.view_y) + dy;
	printf("dx = %f  | dy = %f\n",dx,dy);
	new_x_g = (int )(new_x + 0.5);
	new_y_g = (int )(new_y + 0.85);
	if (new_x_g < 0 || new_y_g < 0 || !vars->t_map.map[new_y_g] || !vars->t_map.map[new_y_g][new_x_g])
		return;
	if (vars->t_map.map[new_y_g ][new_x_g] == '1')
		return;
	vars->player.view_x = (double)new_x;
	vars->player.view_y = (double)new_y;
	vars->player.grid_x = new_x_g;
	vars->player.grid_y = new_y_g;
} 
int	key_pressed_p(int keycode, t_vars *v)
{
	printf("key : %i pressed\n",keycode);
	if (keycode == 65307)
		exit(0);
	if (keycode == 97 || keycode == 65361)
		v->input.left = 1;
	if (keycode == 100 || keycode == 65363)
		v->input.right = 1;
	if (keycode == 119 || keycode == 65362)
		v->input.up = 1;
	if (keycode == 115 || keycode == 65364)
		v->input.down = 1;
	if (keycode == 32)
	{
		printf("SPACE");
		player_jump(v);
	}
	v->moving = 1;
	return (0);
}
int key_handler_p(int keycode, t_vars *v)
{
	if (keycode == 32)
	{
		printf("SPACE");
		player_jump(v);
	}
	return (0);
}

int	key_release_p(int keycode, t_vars *v)
{
	printf("key : %i released\n",keycode);
	if (keycode == 97 || keycode == 65361)
		v->input.left = 0;
	if (keycode == 100 || keycode == 65363)
		v->input.right = 0;
	if (keycode == 119 || keycode == 65362)
		v->input.up = 0;
	if (keycode == 115 || keycode == 65364)
		v->input.down = 0;
		if (keycode == 32)
	v->moving = 0;
	return (0);
}
void	player_jump(t_vars *v)
{
	double jump_power = -0.6;
	double gravity = 1.2;
	double jump_duration = 1.0;
	double dt = 0.016;
	int		start_y;
	if (!v->player.jump)
	{
		v->player.jump_timer = 0.0;
		v->player.jump = 1;
		v->player.vel_y = jump_power;
		start_y = v->player.view_y;
	}

	if (v->player.jump)
	{
		v->player.jump_timer += dt;
		v->player.vel_y += gravity * dt;

		if (v->player.jump_timer >= jump_duration)
		{
			v->player.view_y = start_y;
			v->player.vel_y = 0;
			v->player.jump = 0;
		}
	}
}


// int game_loop(t_vars *v)
// {
// 	int moved = 0;

// 	if (v->keys[97] || v->keys[65361]) // A or Left
// 	{
// 		move_player(v, -0.1, 0);
// 		moved = 1;
// 	}
// 	if (v->keys[100] || v->keys[65363]) // D or Right
// 	{
// 		move_player(v, 0.1, 0);
// 		moved = 1;
// 	}
// 	if (v->keys[119] || v->keys[65362]) // W or Up
// 	{
// 		move_player(v, 0, -0.1);
// 		moved = 1;
// 	}
// 	if (v->keys[115] || v->keys[65364]) // S or Down
// 	{
// 		move_player(v, 0, 0.1);
// 		moved = 1;
// 	}
// 	if (moved)
// 		render_frame(v); 
// 	return (0);
// }

int	game_loop(t_vars *v)
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
	//continu
	// if (v->input.left)
	// 	move_player(v, -0.1, 0);
	// if (v->input.right)
	// 	move_player(v, 0.1, 0);
	// if (v->input.up)
	// 	move_player(v, 0, -0.1);
	// if (v->input.down)
	// 	move_player(v, 0, 0.1);
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
	usleep(16666);
	return (0);
}




void get_player_grid_pos(t_vars *v)
{
	int y = 0;
	while (v->t_map.map[y])
	{
		int x = 0;
		while (v->t_map.map[y][x])
		{
			if (v->t_map.map[y][x] == 'P')
			{
				v->player.grid_x = x;
				v->player.grid_y = y;
				v->player.view_x = (double)x;
				v->player.view_y = (double)y;
				return;
			}
			x++;
		}
		y++;
	}
}


void render_player(t_vars *v)
{
    int px = (v->player.view_x * v->tile_size) - (int)v->t_cam.x;
    int py = (v->player.view_y * v->tile_size) - (int)v->t_cam.y;


    if (!v->tx.player)
    {
        ft_printf("player texture NULL dans render_player\n");
        return;
    }
    mlx_put_image_to_window(v->mlx, v->win, v->tx.player, px, py);
}

