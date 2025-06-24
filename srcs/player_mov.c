/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:35:11 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/24 17:57:46 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int 	is_wall(char c)
{
	if (c == '1' || c == 'D' || c == 'T' || c == 'A' ||
	       c == 'O' || c == 'B' || c == 'R' || c == 'L' || c == 'Z')
			return (1);
	else
		return (0);
}

void move_player(t_vars *vars, double dx, double dy)
{
	double new_x;
	double new_y;
	int new_x_g;
	int new_y_g;

	new_x = vars->player.view_x + dx;

	if (vars->player.jump)
		new_y = vars->player.view_jump + dy; // Utilise view_jump pendant le saut
	else
		new_y = vars->player.view_y + dy;

	new_x_g = (int)(new_x + 0.5);
	new_y_g = (int)(new_y + 0.85);
	
	// Vérifie limites et collision avec mur
	if (new_x_g < 0 || new_y_g < 0 || !vars->t_map.map[new_y_g] || !vars->t_map.map[new_y_g][new_x_g])
		return;

	if (is_wall(vars->t_map.map[new_y_g][new_x_g]))
		return;

	// Met à jour la position horizontale
	vars->player.view_x = new_x;

	// Met à jour la position verticale selon l’état de saut
	if (vars->player.jump)
		vars->player.view_jump = new_y;
	else
	{
		vars->player.view_y = new_y;
		vars->player.view_jump = new_y; // Synchronise view_jump quand pas en saut
	}

	vars->player.grid_x = new_x_g;
	vars->player.grid_y = new_y_g;
}
void	key_pressed_p(int keycode, t_vars *v)
{
	//printf("key : %i pressed\n",keycode);
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
	if (keycode == 32 && v->player.jump == 0)
	{
		v->player.jump = 1;
		v->player.jump_counter = 0;
	}
	v->moving = 1;
	return ;
}

void	key_release_p(int keycode, t_vars *v)
{
	//printf("key : %i released\n",keycode);
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
	return ;
}