/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/23 16:21:36 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_all(t_vars *v)
{
	if (!v)
		return;

	calculate_tile_size_n_mapsize(v);
	calculate_offset(v);
	// init_background(v);
	init_texture(v, &v->tx);
	
	nb_mob(v);
	get_player_grid_pos(v);
	init_coins(v);
	set_all_ennemy(v);
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
}

uint32_t *opt_texture(t_img *img, t_vars *v)
{
    int x = 0;
    int y = 0;
    uint32_t *tx;

    tx = malloc(sizeof(uint32_t) * v->tile_size * v->tile_size);
    if (!tx)
        return NULL;

    while (x < v->tile_size)
    {
        y = 0;
        while (y < v->tile_size)
        {
            int index = y * v->tile_size + x;
            tx[index] = get_pixel(img, x, y);
            y++;
        }
        x++;
    }
	//  if (img->image)
    // {
    //     mlx_destroy_image(v->mlx, img->image);
    //     img->image = NULL;
    //     img->data = NULL;
    // }
    return tx;
}
void print_img(t_img *img)
{
	if (!img)
	{
		printf("Image: NULL\n");
		return;
	}

	printf("  image        : %p\n", (void *)img->image);
	printf("  pix          : %lu\n", (unsigned long)img->pix);
	printf("  gc           : %p\n", (void *)img->gc);
	printf("  size_line    : %d\n", img->size_line);
	printf("  bpp          : %d\n", img->bpp);
	printf("  width        : %d\n", img->width);
	printf("  height       : %d\n", img->height);
	printf("  type         : %d\n", img->type);
	printf("  format       : %d\n", img->format);
	printf("  data         : %p\n", (void *)img->data);
	printf("  shm.shmid    : %d\n", img->shm.shmid);
	printf("  shm.shmaddr  : %p\n", img->shm.shmaddr);
	printf("  shm.readOnly : %d\n", img->shm.readOnly);
}

void	init_texture(t_vars *v, t_texture *txt)
{
	if (!txt)
		return;
	init_img_struct(&txt->wall.bottom);
	init_img_struct(&txt->wall.top);
	init_img_struct(&txt->wall.left);
	init_img_struct(&txt->wall.right);
	init_img_struct(&txt->wall.middle);
	init_img_struct(&txt->wall.corner);
	init_img_struct(&txt->ground);
	init_img_struct(&txt->coin);
	init_img_struct(&txt->player);
	init_img_struct(&txt->exit);
	init_img_struct(&txt->shadow);
    init_img_struct(&txt->mob);
	get_img(v, &txt->ground, "ground");
	get_img(v, &txt->coin, "coin_0");
	get_img(v, &txt->player, "player_1");
	get_img(v, &txt->exit, "exit");
	get_img(v, &txt->shadow, "shadow");
	get_img(v, &txt->wall.top, "wall_1");
	get_img(v, &txt->wall.bottom, "wall_bottom");
	get_img(v, &txt->wall.right, "wall_right");
	get_img(v, &txt->wall.left, "wall_left");
	get_img(v, &txt->wall.middle, "chair");
	get_img(v, &txt->wall.corner, "corner");
    get_img(v, &txt->mob, "mob");
    // printf("mob data : \n",v->tx.player.data);
    // print_img(&v->tx.mob);
    // print_img(&v->tx.player);
	transfer_tx(v);

	init_frame(v, &v->frame, RES_X, RES_Y);

}

void dump_texture(uint32_t *texture, int length)
{
    FILE *f = fopen("test.txt", "w");
    if (!f)
    {
        perror("Erreur ouverture fichier");
        return;
    }
    
    for (int i = 0; i < length; i++)
    {
        if (i > 0 && i % 200 == 0)
            fputc('\n', f);

        if (texture[i] == 0x000000)
            fputc(' ', f);
        else
            fputc('x', f);
    }
    fputc('\n', f);
    fclose(f);
}

void transfer_tx(t_vars *v)
{
	v->opt_txt.wall[0] = opt_texture(&v->tx.wall.top, v);
    v->opt_txt.wall[1] = opt_texture(&v->tx.wall.bottom, v);
    v->opt_txt.wall[2] = opt_texture(&v->tx.wall.left, v);
    v->opt_txt.wall[3] = opt_texture(&v->tx.wall.right, v);
    v->opt_txt.wall[4] = opt_texture(&v->tx.wall.corner, v);
    v->opt_txt.wall[5] = opt_texture(&v->tx.wall.middle, v);
    v->opt_txt.ground = opt_texture(&v->tx.ground, v);
    v->opt_txt.exit = opt_texture(&v->tx.exit, v);
	v->opt_txt.coin = opt_texture(&v->tx.coin, v);
	v->opt_txt.player = opt_texture(&v->tx.player, v);
	v->opt_txt.shadow = opt_texture(&v->tx.shadow, v);
    v->opt_txt.mob = opt_texture(&v->tx.mob, v);
 
    // dump_texture(v->opt_txt.mob,200*200);
}
#include <stdio.h>
#include <stdint.h>

