/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/04 11:44:33 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_all(t_vars *v)
{
	if (!v)
		return ;
	calculate_tile_size_n_mapsize(v);
	calculate_offset(v);
	v->t_cam.x = 0;
	v->t_cam.y = 0;
	v->overlay = NULL;
	get_player_grid_pos(v);
	init_texture(v);
	nb_mob(v);
	init_coins(v);
	set_all_ennemy(v);
	get_exit(v);
	v->fps = 0;
	v->case_move = 0;
}

void	init_img_struct(t_img *txt)
{
	if (!txt)
		return ;
	ft_memset(txt, 0, sizeof(t_img));
	txt->shm.shmid = -1;
	txt->shm.shmaddr = (char *)-1;
	txt->shm.readOnly = False;
}

void	init_texture(t_vars *v)
{
	int		h;
	int		w;
	char	*path;

	path = ft_sprintf("assets/overlay.xpm");
	h = 100;
	w = 1920;
	init_frame(v, &v->frame, 1920, 1080);
	init_all_img_struct(&v->tx);
	get_all_img(v, &v->tx);
	v->overlay = mlx_xpm_file_to_image(v->mlx, path, &h, &w);
	free(path);
	check_texture(v);
	transfer_tx_1(v);
	transfer_tx(v);
}

void	transfer_tx_1(t_vars *v)
{
	v->opt_txt.player[0] = opt_texture(&v->tx.player[0], v);
	v->opt_txt.player[1] = opt_texture(&v->tx.player[1], v);
	v->opt_txt.player[2] = opt_texture(&v->tx.player[2], v);
	v->opt_txt.player[3] = opt_texture(&v->tx.player[3], v);
	v->opt_txt.player[4] = opt_texture(&v->tx.player[4], v);
	v->opt_txt.player[5] = opt_texture(&v->tx.player[5], v);
	v->opt_txt.p_right[0] = mirror_texture(v->opt_txt.player[0], v->tile_size);
	v->opt_txt.p_right[1] = mirror_texture(v->opt_txt.player[1], v->tile_size);
	v->opt_txt.p_right[2] = mirror_texture(v->opt_txt.player[2], v->tile_size);
	v->opt_txt.p_right[3] = mirror_texture(v->opt_txt.player[3], v->tile_size);
	v->opt_txt.p_right[4] = mirror_texture(v->opt_txt.player[4], v->tile_size);
	v->opt_txt.p_right[5] = mirror_texture(v->opt_txt.player[5], v->tile_size);
	v->opt_txt.ground = opt_texture(&v->tx.ground, v);
	v->opt_txt.coin = opt_texture(&v->tx.coin, v);
	v->opt_txt.exit = opt_texture(&v->tx.exit, v);
	v->opt_txt.shadow = opt_texture(&v->tx.shadow, v);
	v->opt_txt.wall[0] = opt_texture(&v->tx.wall.top, v);
	v->opt_txt.wall[1] = opt_texture(&v->tx.wall.bottom, v);
	v->opt_txt.wall[2] = opt_texture(&v->tx.wall.left, v);
	v->opt_txt.wall[3] = opt_texture(&v->tx.wall.right, v);
	v->opt_txt.wall[4] = opt_texture(&v->tx.wall.corner_tl, v);
	v->opt_txt.wall[5] = opt_texture(&v->tx.wall.corner_tr, v);
	v->opt_txt.wall[6] = opt_texture(&v->tx.wall.corner_bl, v);
	v->opt_txt.wall[7] = opt_texture(&v->tx.wall.corner_br, v);
	v->opt_txt.wall[8] = opt_texture(&v->tx.wall.middle, v);
}

void	transfer_tx(t_vars *v)
{
	v->opt_txt.jump = opt_texture(&v->tx.jump, v);
	v->opt_txt.mob = opt_texture(&v->tx.mob, v);
	v->opt_txt.placeholder = opt_texture(&v->tx.placeholder, v);
	v->opt_txt.jump_r = mirror_texture(v->opt_txt.jump, v->tile_size);
}
