/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 12:33:56 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_camera(t_vars *v)
{
	double	target_y;
	double	target_x;
	double	lerp_factor;

	target_x = v->player.view_x * v->tile_size - RES_X / 2;
	if (!v->player.jump)
		target_y = v->player.view_y * v->tile_size - RES_Y / 2;
	else
		target_y = v->player.view_jump * v->tile_size - RES_Y / 2;
	lerp_factor = 0.08;
	v->t_cam.x += (target_x - v->t_cam.x) * lerp_factor;
	v->t_cam.y += (target_y - v->t_cam.y) * lerp_factor;
}

void	put_text(t_vars *v)
{
	char	*count_mouve ;
	char	*count_coin;
	char	*fps;
	char	*case_move;

	case_move = ft_sprintf("MOVES CASES = %i", v->case_move);
	fps = ft_sprintf("FPS = %i", v->fps);
	count_mouve = ft_sprintf("MOVES = %i", v->mouv_counter);
	count_coin = ft_sprintf("SERINGUES = %i/%i", v->coin_get, v->coin_count);
	mlx_string_put(v->mlx, v->win, 50, 50, 0x46eb34, count_mouve);
	mlx_string_put(v->mlx, v->win, 50, 70, 0x111111, case_move);
	mlx_string_put(v->mlx, v->win, 450, 50, 0x111111, count_coin);
	if (v->fps < 30)
		mlx_string_put(v->mlx, v->win, 1500, 50, 0x000000, fps);
	else
		mlx_string_put(v->mlx, v->win, 1500, 50, 0x000000, "FPS = 30");
	free(count_coin);
	free(count_mouve);
	free(case_move);
	free(fps);
}

void	render_frame(t_vars *v)
{
	memset(v->frame.data, 0, v->frame.height * v->frame.size_line);
	draw_frame(v);
	mlx_put_image_to_window(v->mlx, v->win, v->frame.image, 0, 0);
	mlx_put_image_to_window(v->mlx, v->win, v->overlay, 0, 0);
	put_text(v);
}

int	init_frame(t_vars *v, t_img *frame, int width, int height)
{
	int	endian;

	frame->width = width;
	frame->height = height;
	frame->image = mlx_new_image(v->mlx, width, height);
	if (!frame->image)
	{
		ft_printf("Erreur : mlx_new_image a échoué\n");
		return (1);
	}
	frame->data = mlx_get_data_addr(frame->image,
			&frame->bpp, &frame->size_line, &endian);
	if (!frame->data)
	{
		ft_printf("Erreur : mlx_get_data_addr a retourné NULL\n");
		return (1);
	}
	memset(frame->data, 0, height * frame->size_line);
	return (0);
}
