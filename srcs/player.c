/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:26:17 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/17 18:17:15 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_vars *vars, double dx, double dy)
{
	double	new_x;
	double	new_y;
	int		new_x_g;
	int		new_y_g;
	
	new_x = (vars->player.view_x) + dx;
	new_y = (vars->player.view_y) + dy;
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
int	key_handler_p(int keycode, t_vars *v)
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
	return (0);
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
	double dx = 0;
	double dy = 0;
	double	m_speed;
	int i; 
	
	i = 0;
	m_speed = 0.055;
	if (v->input.left)
		dx -= m_speed;
	if (v->input.right)
		dx += m_speed;
	if (v->input.up)
		dy -= m_speed;
	if (v->input.down)
		dy +=	m_speed;
	if (dx != 0 || dy != 0)
		move_player(v, dx, dy);
	i = 0;
	while (i < v->coin_count)
	{	
		if (v->player.grid_x == v->coin[i].cx && v->player.grid_y == v->coin[i].cy)
			v->coin[i].vis = 0;
		i++;
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
