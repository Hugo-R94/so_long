/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:00:00 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/04 11:11:17 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_opt_texture(uint32_t **texture)
{
	if (texture && *texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

static void	free_mlx_image(t_vars *v, t_img *img)
{
	if (!v || !img)
		return ;
	if (v->mlx && img->image)
	{
		mlx_destroy_image(v->mlx, img->image);
		img->image = NULL;
	}
	img->data = NULL;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->size_line = 0;
}

void	cleanup_optimized_textures(t_vars *v)
{
	int	i;

	if (!v)
		return ;
	i = -1;
	while (++i < 6)
		free_opt_texture(&v->opt_txt.player[i]);
	i = -1;
	while (++i < 6)
		free_opt_texture(&v->opt_txt.p_right[i]);
	i = -1;
	while (++i < 9)
		free_opt_texture(&v->opt_txt.wall[i]);
	free_opt_texture(&v->opt_txt.ground);
	free_opt_texture(&v->opt_txt.coin);
	free_opt_texture(&v->opt_txt.exit);
	free_opt_texture(&v->opt_txt.shadow);
	free_opt_texture(&v->opt_txt.jump);
	free_opt_texture(&v->opt_txt.jump_r);
	free_opt_texture(&v->opt_txt.mob);
	free_opt_texture(&v->opt_txt.placeholder);
}

void	cleanup_mlx_textures(t_vars *v)
{
	int	i;

	if (!v)
		return ;
	i = -1;
	while (++i < 6)
		free_mlx_image(v, &v->tx.player[i]);
	free_mlx_image(v, &v->tx.wall.top);
	free_mlx_image(v, &v->tx.wall.bottom);
	free_mlx_image(v, &v->tx.wall.left);
	free_mlx_image(v, &v->tx.wall.right);
	free_mlx_image(v, &v->tx.wall.corner_tl);
	free_mlx_image(v, &v->tx.wall.corner_tr);
	free_mlx_image(v, &v->tx.wall.corner_bl);
	free_mlx_image(v, &v->tx.wall.corner_br);
	free_mlx_image(v, &v->tx.wall.middle);
	free_mlx_image(v, &v->tx.ground);
	free_mlx_image(v, &v->tx.coin);
	free_mlx_image(v, &v->tx.exit);
	free_mlx_image(v, &v->tx.shadow);
	free_mlx_image(v, &v->tx.jump);
	free_mlx_image(v, &v->tx.mob);
	free_mlx_image(v, &v->tx.placeholder);
}

void	cleanup_frame(t_vars *v)
{
	if (!v)
		return ;
	free_mlx_image(v, &v->frame);
}
