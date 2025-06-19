/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/19 14:36:59 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void update_camera(t_vars *v)
{
    double target_x = v->player.view_x * v->tile_size - RES_X / 2;
    double target_y = v->player.view_y * v->tile_size - RES_Y / 2;
    double lerp_factor = 0.08;
    v->t_cam.x += (target_x - v->t_cam.x) * lerp_factor;
    v->t_cam.y += (target_y - v->t_cam.y) * lerp_factor;
}


void render_frame(t_vars *v)
{
	int i = 0;
    memset(v->frame.data, 0, v->frame.height * v->frame.size_line); // nettoie frame

    draw_background(v, &v->frame);
    // render_coin(v, &v->frame); // si tu en as
	while (i < v->coin_count)
    		draw_coin(v, i++);
    draw_player(v);
	g
    mlx_put_image_to_window(v->mlx, v->win, v->frame.image, 0, 0);
}

int init_frame(t_vars *v, t_img *frame, int width, int height)
{
	int endian;

	frame->width = width;
	frame->height = height;

	frame->image = (XImage *)mlx_new_image(v->mlx, width, height);
	if (!frame->image)
	{
		ft_printf("Erreur : mlx_new_image a échoué\n");
		return (1);
	}

	frame->data = mlx_get_data_addr((void *)frame->image, &frame->bpp, &frame->size_line, &endian);
	if (!frame->data)
	{
		ft_printf("Erreur : mlx_get_data_addr a retourné NULL\n");
		return (1);
	}

	memset(frame->data, 0, height * frame->size_line);

	return (0);
}

