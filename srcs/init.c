/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/01 16:59:00 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
static void transfer_tx_1(t_vars *v);

void	init_all(t_vars *v)
{
	if (!v)
		return;
	calculate_tile_size_n_mapsize(v);
	calculate_offset(v);
	v->t_cam.x = 0;
	v->t_cam.y = 0;
	v->fps = 0;
	v->overlay = NULL;
	get_player_grid_pos(v);
	init_texture(v);
	nb_mob(v);
	init_coins(v);
	set_all_ennemy(v);
	get_exit(v);
}


void	init_img_struct(t_img *txt)
{
	if (!txt)
		return;
	ft_memset(txt, 0, sizeof(t_img));
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
		free(path);
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
	 if (img->image)
    {
        mlx_destroy_image(v->mlx, img->image);
        img->image = NULL;
        img->data = NULL;
    }
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

void	init_all_img_struct(t_texture *txt)
{
	init_img_struct(&txt->player[0]);
	init_img_struct(&txt->player[1]);
	init_img_struct(&txt->player[2]);
	init_img_struct(&txt->player[3]);
	init_img_struct(&txt->player[4]);
	init_img_struct(&txt->player[5]);
	init_img_struct(&txt->ground);
	init_img_struct(&txt->coin);
	init_img_struct(&txt->exit);
	init_img_struct(&txt->shadow);
	init_img_struct(&txt->wall.top);
	init_img_struct(&txt->wall.bottom);
	init_img_struct(&txt->wall.left);
	init_img_struct(&txt->wall.right);
	init_img_struct(&txt->wall.corner_tl);
	init_img_struct(&txt->wall.corner_tr);
	init_img_struct(&txt->wall.corner_bl);
	init_img_struct(&txt->wall.corner_br);
	init_img_struct(&txt->wall.middle);
	init_img_struct(&txt->jump);
	init_img_struct(&txt->mob);
	init_img_struct(&txt->placeholder);
}

void	get_all_img(t_vars *v, t_texture *txt)
{
	get_img(v, &txt->player[0], "hulk_0");
	get_img(v, &txt->player[1], "hulk_1");
	get_img(v, &txt->player[2], "hulk_2");
	get_img(v, &txt->player[3], "hulk_3");
	get_img(v, &txt->player[4], "hulk_4");
	get_img(v, &txt->player[5], "hulk_5");
	get_img(v, &txt->ground, "ground");
	get_img(v, &txt->coin, "coin_0");
	get_img(v, &txt->exit, "exit");
	get_img(v, &txt->shadow, "shadow");
	get_img(v, &txt->wall.top, "wall_T");
	get_img(v, &txt->wall.bottom, "wall_B");
	get_img(v, &txt->wall.left, "wall_L");
	get_img(v, &txt->wall.right, "wall_R");
	get_img(v, &txt->wall.corner_tl, "corner_TL");
	get_img(v, &txt->wall.corner_tr, "corner_TR");
	get_img(v, &txt->wall.corner_bl, "corner_BL");
	get_img(v, &txt->wall.corner_br, "corner_BR");
	get_img(v, &txt->wall.middle, "chair");
	get_img(v, &txt->jump, "jump");
	get_img(v, &txt->mob, "mob");
	get_img(v, &txt->placeholder, "player_1");
}

void	init_texture(t_vars *v)
{
	
	init_all_img_struct(&v->tx);
	get_all_img(v, &v->tx);
	transfer_tx_1(v);
	transfer_tx(v);
	init_frame(v, &v->frame, 1920, 1080);
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
uint32_t *mirror_texture(uint32_t *src, int tile_size)
{
   	uint32_t *dst = malloc(sizeof(uint32_t) * tile_size * tile_size);
	int y;
	int x;
    if (!dst)
		return NULL;
	y = 0;
 	while (y < tile_size)
    {
		x = 0;
    	while (x < tile_size)
        {
			dst[y * tile_size + x] = src[y * tile_size + (tile_size - 1 - x)];
			x++;
		}
		y++;
    }
    return dst;
}
static void transfer_tx_1(t_vars *v)
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

void transfer_tx(t_vars *v)
{
	int height;
	int width;
	
	height = 100;
	width = 1920;
	v->opt_txt.jump = opt_texture(&v->tx.jump, v);
	v->opt_txt.mob = opt_texture(&v->tx.mob, v);
	v->opt_txt.placeholder = opt_texture(&v->tx.placeholder, v);
	v->opt_txt.jump_r = mirror_texture(v->opt_txt.jump, v->tile_size);
	v->overlay = mlx_xpm_file_to_image(v->mlx,"placeholder_assets/overlay.xpm",&height, &width);
	//dump_texture(v->overlay, 19200);
}