/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/19 14:29:17 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_all(t_vars *v)
{
	if (!v)
		return;
	init_texture(v, &v->tx);
	// init_background(v);
	calculate_tile_size_n_mapsize(v);
	calculate_offset(v);
	get_player_grid_pos(v);
	init_coins(v);
	get_exit(v);
	
	// init_player(v);
	// init_coins(v);
	// init_camera(v);
}


void	init_img_struct(t_img *txt)
{
		if (!txt)
		return;

	ft_memset(txt, 0, sizeof(t_img));

	txt->image = NULL;
	txt->pix = 0;
	txt->gc = 0;
	txt->size_line = 0;
	txt->bpp = 32;
	txt->width = 0;
	txt->height = 0;
	txt->type = 0;
	txt->format = 0;
	txt->data = NULL;

	txt->shm.shmid = -1;
	txt->shm.shmaddr = (char *)-1;
	txt->shm.readOnly = False;
}

void get_img(t_vars *v, t_img *img, const char *txt_name)
{
    char    *path;
    int     len;
    int     endian; // variable temporaire

    len = ft_strlen("placeholder_assets/") + ft_strlen(txt_name) + ft_strlen(".xpm") + 1;
    path = malloc(len);
    if (!path)
    {
        write(2, "Erreur : malloc échoué dans get_img\n", 37);
        exit(EXIT_FAILURE);
    }
    ft_strcpy(path, "placeholder_assets/");
    ft_strcat(path, txt_name);
    ft_strcat(path, ".xpm");

    img->image = mlx_xpm_file_to_image(v->mlx, path, &img->width, &img->height);
    free(path);

    if (!img->image)
    {
        ft_printf("Erreur : %s.xpm a échoué à se charger.\n", txt_name);
        exit(EXIT_FAILURE);
    }

    img->data = mlx_get_data_addr(img->image, &img->bpp, &img->size_line, &endian);
    if (!img->data)
    {
        ft_printf("Erreur : impossible de récupérer data pour %s\n", txt_name);
        exit(EXIT_FAILURE);
    }
	printf("Image '%s' chargée : width=%d, height=%d, bpp=%d, size_line=%d, data=%p\n",
        txt_name, img->width, img->height, img->bpp, img->size_line, (void *)img->data);
}


void	init_texture(t_vars *v, t_texture *txt)
{
	if (!txt)
		return;
	//init img to NULL
	init_img_struct(&txt->wall);
	init_img_struct(&txt->ground);
	init_img_struct(&txt->coin);
	init_img_struct(&txt->player);
	init_img_struct(&txt->exit);

	//get images
	get_img(v, &txt->wall, "wall_1");
	get_img(v, &txt->ground, "ground");
	get_img(v, &txt->coin, "coin_0");
	get_img(v, &txt->player, "player_1");
	get_img(v, &txt->exit, "exit");

	init_frame(v, &v->frame, RES_X, RES_Y);
}