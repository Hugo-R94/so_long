/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:16:09 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 14:33:10 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	*opt_texture(t_img *img, t_vars *v)
{
	int			x;
	int			y;
	uint32_t	*tx;
	int			index;

	tx = malloc(sizeof(uint32_t) * v->tile_size * v->tile_size);
	if (!tx)
		return (NULL);
	x = -1;
	while (++x < v->tile_size)
	{
		y = -1;
		while (++y < v->tile_size)
		{
			index = y * v->tile_size + x;
			tx[index] = get_pixel(img, x, y);
		}
	}
	if (img->image)
	{
		mlx_destroy_image(v->mlx, img->image);
		img->image = NULL;
		img->data = NULL;
	}
	return (tx);
}

uint32_t	*mirror_texture(uint32_t *src, int tile_size)
{
	uint32_t	*dst;
	int			y;
	int			x;

	dst = malloc(sizeof(uint32_t) * tile_size * tile_size);
	if (!dst)
		return (NULL);
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
	return (dst);
}

void	get_img(t_vars *v, t_img *img, const char *txt_name)
{
	char	*path;
	int		len;
	int		endian;

	len = ft_strlen("placeholder_assets/")
		+ ft_strlen(txt_name) + ft_strlen(".xpm") + 1;
	path = malloc(len);
	if (!path)
	{
		free(path);
		exit(EXIT_FAILURE);
	}
	ft_strcpy(path, "placeholder_assets/");
	ft_strcat(path, txt_name);
	ft_strcat(path, ".xpm");
	img->image = mlx_xpm_file_to_image(v->mlx, path, &img->width, &img->height);
	free(path);
	if (!img->image)
		exit(EXIT_FAILURE);
	img->data = mlx_get_data_addr(img->image, &img->bpp,
			&img->size_line, &endian);
	if (!img->data)
		exit(EXIT_FAILURE);
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

// void dump_texture(uint32_t *texture, int length)
// {
// 	FILE *f = fopen("test.txt", "w");
// 	if (!f)
// 	{
// 		perror("Erreur ouverture fichier");
// 		return;
// 	}

// 	for (int i = 0; i < length; i++)
// 	{
// 		if (i > 0 && i % 200 == 0)
// 			fputc('\n', f);

// 		if (texture[i] == 0x000000)
// 			fputc(' ', f);
// 		else
// 			fputc('x', f);
// 	}
// 	fputc('\n', f);
// 	fclose(f);
// }

// void print_img(t_img *img)
// {
// 	if (!img)
// 	{
// 		printf("Image: NULL\n");
// 		return;
// 	}

// 	printf("  image        : %p\n", (void *)img->image);
// 	printf("  pix          : %lu\n", (unsigned long)img->pix);
// 	printf("  gc           : %p\n", (void *)img->gc);
// 	printf("  size_line    : %d\n", img->size_line);
// 	printf("  bpp          : %d\n", img->bpp);
// 	printf("  width        : %d\n", img->width);
// 	printf("  height       : %d\n", img->height);
// 	printf("  type         : %d\n", img->type);
// 	printf("  format       : %d\n", img->format);
// 	printf("  data         : %p\n", (void *)img->data);
// 	printf("  shm.shmid    : %d\n", img->shm.shmid);
// 	printf("  shm.shmaddr  : %p\n", img->shm.shmaddr);
// 	printf("  shm.readOnly : %d\n", img->shm.readOnly);
// }
