/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:00:00 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 12:01:40 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Libère une texture optimisée (uint32_t*)
 */
static void free_opt_texture(uint32_t **texture)
{
    if (texture && *texture)
    {
        free(*texture);
        *texture = NULL;
    }
}

static void free_mlx_image(t_vars *v, t_img *img)
{
    if (!img)
        return;
    
    if (img->image)
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

void cleanup_optimized_textures(t_vars *v)
{
	int i;
	
    if (!v)
        return;
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

void cleanup_mlx_textures(t_vars *v)
{
	int i;
    if (!v)
        return;
    i = -1;
    while (i++ < 6)	
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


void cleanup_frame(t_vars *v)
{
    if (!v)
        return;
    free_mlx_image(v, &v->frame);
}

void cleanup_all_textures(t_vars *v)
{
    if (!v)
    {
        //printf("cleanup_all_textures: pointeur v NULL\n");
        return;
    }
    //printf("Début du nettoyage des textures...\n");
    cleanup_optimized_textures(v);
    cleanup_mlx_textures(v);
    cleanup_frame(v);
    //printf("Nettoyage terminé !\n");
}


// void emergency_cleanup(t_vars *v)
// {
// 	if (!v)
// 		return;

// 	if (v->opt_txt.player[0]) { free(v->opt_txt.player[0]); v->opt_txt.player[0] = NULL; }
// 	if (v->opt_txt.player[1]) { free(v->opt_txt.player[1]); v->opt_txt.player[1] = NULL; }
// 	if (v->opt_txt.player[2]) { free(v->opt_txt.player[2]); v->opt_txt.player[2] = NULL; }
// 	if (v->opt_txt.player[3]) { free(v->opt_txt.player[3]); v->opt_txt.player[3] = NULL; }
// 	if (v->opt_txt.player[4]) { free(v->opt_txt.player[4]); v->opt_txt.player[4] = NULL; }
// 	if (v->opt_txt.player[5]) { free(v->opt_txt.player[5]); v->opt_txt.player[5] = NULL; }

// 	if (v->opt_txt.p_right[0]) { free(v->opt_txt.p_right[0]); v->opt_txt.p_right[0] = NULL; }
// 	if (v->opt_txt.p_right[1]) { free(v->opt_txt.p_right[1]); v->opt_txt.p_right[1] = NULL; }
// 	if (v->opt_txt.p_right[2]) { free(v->opt_txt.p_right[2]); v->opt_txt.p_right[2] = NULL; }
// 	if (v->opt_txt.p_right[3]) { free(v->opt_txt.p_right[3]); v->opt_txt.p_right[3] = NULL; }
// 	if (v->opt_txt.p_right[4]) { free(v->opt_txt.p_right[4]); v->opt_txt.p_right[4] = NULL; }
// 	if (v->opt_txt.p_right[5]) { free(v->opt_txt.p_right[5]); v->opt_txt.p_right[5] = NULL; }

// 	if (v->opt_txt.wall[0]) { free(v->opt_txt.wall[0]); v->opt_txt.wall[0] = NULL; }
// 	if (v->opt_txt.wall[1]) { free(v->opt_txt.wall[1]); v->opt_txt.wall[1] = NULL; }
// 	if (v->opt_txt.wall[2]) { free(v->opt_txt.wall[2]); v->opt_txt.wall[2] = NULL; }
// 	if (v->opt_txt.wall[3]) { free(v->opt_txt.wall[3]); v->opt_txt.wall[3] = NULL; }
// 	if (v->opt_txt.wall[4]) { free(v->opt_txt.wall[4]); v->opt_txt.wall[4] = NULL; }
// 	if (v->opt_txt.wall[5]) { free(v->opt_txt.wall[5]); v->opt_txt.wall[5] = NULL; }
// 	if (v->opt_txt.wall[6]) { free(v->opt_txt.wall[6]); v->opt_txt.wall[6] = NULL; }
// 	if (v->opt_txt.wall[7]) { free(v->opt_txt.wall[7]); v->opt_txt.wall[7] = NULL; }
// 	if (v->opt_txt.wall[8]) { free(v->opt_txt.wall[8]); v->opt_txt.wall[8] = NULL; }

// 	if (v->opt_txt.ground) { free(v->opt_txt.ground); v->opt_txt.ground = NULL; }
// 	if (v->opt_txt.coin) { free(v->opt_txt.coin); v->opt_txt.coin = NULL; }
// 	if (v->opt_txt.exit) { free(v->opt_txt.exit); v->opt_txt.exit = NULL; }
// 	if (v->opt_txt.shadow) { free(v->opt_txt.shadow); v->opt_txt.shadow = NULL; }
// 	if (v->opt_txt.jump) { free(v->opt_txt.jump); v->opt_txt.jump = NULL; }
// 	if (v->opt_txt.jump_r) { free(v->opt_txt.jump_r); v->opt_txt.jump_r = NULL; }
// 	if (v->opt_txt.mob) { free(v->opt_txt.mob); v->opt_txt.mob = NULL; }
// 	if (v->opt_txt.placeholder) { free(v->opt_txt.placeholder); v->opt_txt.placeholder = NULL; }
// }
static void	emergency_cleanup_sub(t_vars *v)
{
	int i;
	
	i = -1;
	while (++i < 6)
	{
		if (v->opt_txt.player[i])
		{
			free(v->opt_txt.player[i]);
			v->opt_txt.player[i] = NULL;
		}
		if (v->opt_txt.p_right[i])
		{
			free(v->opt_txt.p_right[0]);
			v->opt_txt.p_right[1] = NULL;
		}
		if (v->opt_txt.wall[0])
		{
			
		}
	}
}
void emergency_cleanup(t_vars *v)
{
	int i;
	
	if (!v)
		return;
	emergency_cleanup_sub(v);
	i = -1;
	while (++i < 9)
	{
		if (v->opt_txt.wall[i])
			{
				free(v->opt_txt.wall[1]);
				v->opt_txt.wall[2] = NULL;
			}
	}
	if (v->opt_txt.ground) { free(v->opt_txt.ground); v->opt_txt.ground = NULL; }
	if (v->opt_txt.coin) { free(v->opt_txt.coin); v->opt_txt.coin = NULL; }
	if (v->opt_txt.exit) { free(v->opt_txt.exit); v->opt_txt.exit = NULL; }
	if (v->opt_txt.shadow) { free(v->opt_txt.shadow); v->opt_txt.shadow = NULL; }
	if (v->opt_txt.jump) { free(v->opt_txt.jump); v->opt_txt.jump = NULL; }
	if (v->opt_txt.jump_r) { free(v->opt_txt.jump_r); v->opt_txt.jump_r = NULL; }
	if (v->opt_txt.mob) { free(v->opt_txt.mob); v->opt_txt.mob = NULL; }
	if (v->opt_txt.placeholder) { free(v->opt_txt.placeholder); v->opt_txt.placeholder = NULL; }
}
static void free_vars_resources(t_vars *v)
{
    if (v->frame.image)
    {
        mlx_destroy_image(v->mlx, v->frame.image);
        v->frame.image = NULL;
    }
	if (v->overlay)
		mlx_destroy_image(v->mlx, v->overlay);
    if (v->img)
    {
        mlx_destroy_image(v->mlx, v->img);
        v->img = NULL;
    }
    if (v->win)
    {
        mlx_destroy_window(v->mlx, v->win);
        v->win = NULL;
    }
    if (v->mlx)
    {
        mlx_destroy_display(v->mlx);
        free(v->mlx);
        v->mlx = NULL;
    }
}

int	clean_and_exit(t_vars *v)
{
    if (!v)
        return (0);
    free_vars_resources(v);
    if (v->coin)
    {
        free(v->coin);
        v->coin = NULL;
    }
    if (v->mob)
    {
        free(v->mob);
        v->mob = NULL;
    }
    cleanup_all_textures(v);
    free_tab(v->t_map.map);
    free(v);
    exit(EXIT_SUCCESS);
    return (0);
}
