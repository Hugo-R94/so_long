/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 00:00:00 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/27 15:11:03 by hugz             ###   ########.fr       */
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

/**
 * Libère une image MLX et remet les pointeurs à NULL
 */
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

/**
 * Libère toutes les textures optimisées (opt_txt)
 */
void cleanup_optimized_textures(t_vars *v)
{
    if (!v)
        return;
    
    // Libère les textures du joueur (gauche)
    for (int i = 0; i < 6; i++)
        free_opt_texture(&v->opt_txt.player[i]);

    // Libère les textures du joueur (droite - miroir)
    for (int i = 0; i < 6; i++)
        free_opt_texture(&v->opt_txt.p_right[i]);
    
    // Libère les textures des murs
    for (int i = 0; i < 9; i++)
        free_opt_texture(&v->opt_txt.wall[i]);
    
    // Libère les autres textures
    free_opt_texture(&v->opt_txt.ground);
    free_opt_texture(&v->opt_txt.coin);
    free_opt_texture(&v->opt_txt.exit);
    free_opt_texture(&v->opt_txt.shadow);
    free_opt_texture(&v->opt_txt.jump);
    free_opt_texture(&v->opt_txt.jump_r);
    free_opt_texture(&v->opt_txt.mob);
    free_opt_texture(&v->opt_txt.placeholder);
    
    printf("✅ Textures optimisées libérées\n");
}

/**
 * Libère toutes les images MLX originales (tx)
 */
void cleanup_mlx_textures(t_vars *v)
{
    if (!v)
        return;
    
    // Libère les images du joueur
    for (int i = 0; i < 6; i++)
        free_mlx_image(v, &v->tx.player[i]);
    
    // Libère les images des murs
    free_mlx_image(v, &v->tx.wall.top);
    free_mlx_image(v, &v->tx.wall.bottom);
    free_mlx_image(v, &v->tx.wall.left);
    free_mlx_image(v, &v->tx.wall.right);
    free_mlx_image(v, &v->tx.wall.corner_tl);
    free_mlx_image(v, &v->tx.wall.corner_tr);
    free_mlx_image(v, &v->tx.wall.corner_bl);
    free_mlx_image(v, &v->tx.wall.corner_br);
    free_mlx_image(v, &v->tx.wall.middle);
    
    // Libère les autres images
    free_mlx_image(v, &v->tx.ground);
    free_mlx_image(v, &v->tx.coin);
    free_mlx_image(v, &v->tx.exit);
    free_mlx_image(v, &v->tx.shadow);
    free_mlx_image(v, &v->tx.jump);
    free_mlx_image(v, &v->tx.mob);
    free_mlx_image(v, &v->tx.placeholder);
    
    printf("✅ Images MLX libérées\n");
}

/**
 * Libère l'image de frame
 */
void cleanup_frame(t_vars *v)
{
    if (!v)
        return;
    
    free_mlx_image(v, &v->frame);
    printf("✅ Frame libérée\n");
}

/**
 * FONCTION PRINCIPALE - Libère TOUTES les textures
 * À appeler avant exit() ou dans ton signal handler
 */
void cleanup_all_textures(t_vars *v)
{
    if (!v)
    {
        printf("❌ cleanup_all_textures: pointeur v NULL\n");
        return;
    }
    
    printf("🧹 Début du nettoyage des textures...\n");
    
    // 1. Libère les textures optimisées (malloc)
    cleanup_optimized_textures(v);
    
    // 2. Libère les images MLX (déjà fait dans opt_texture mais on s'assure)
    cleanup_mlx_textures(v);
    
    // 3. Libère la frame
    cleanup_frame(v);
    
    printf("✅ Nettoyage terminé !\n");
}

/**
 * Version d'urgence pour les cas d'erreur
 * Plus robuste mais moins bavarde
 */
void emergency_cleanup(t_vars *v)
{
    if (!v)
        return;
    
    // Libère opt_txt sans printf
    for (int i = 0; i < 6; i++)
    {
        if (v->opt_txt.player[i]) { free(v->opt_txt.player[i]); v->opt_txt.player[i] = NULL; }
        if (v->opt_txt.p_right[i]) { free(v->opt_txt.p_right[i]); v->opt_txt.p_right[i] = NULL; }
    }
    
    for (int i = 0; i < 9; i++)
        if (v->opt_txt.wall[i]) { free(v->opt_txt.wall[i]); v->opt_txt.wall[i] = NULL; }
    
    if (v->opt_txt.ground) { free(v->opt_txt.ground); v->opt_txt.ground = NULL; }
    if (v->opt_txt.coin) { free(v->opt_txt.coin); v->opt_txt.coin = NULL; }
    if (v->opt_txt.exit) { free(v->opt_txt.exit); v->opt_txt.exit = NULL; }
    if (v->opt_txt.shadow) { free(v->opt_txt.shadow); v->opt_txt.shadow = NULL; }
    if (v->opt_txt.jump) { free(v->opt_txt.jump); v->opt_txt.jump = NULL; }
    if (v->opt_txt.jump_r) { free(v->opt_txt.jump_r); v->opt_txt.jump_r = NULL; }
    if (v->opt_txt.mob) { free(v->opt_txt.mob); v->opt_txt.mob = NULL; }
    if (v->opt_txt.placeholder) { free(v->opt_txt.placeholder); v->opt_txt.placeholder = NULL; }
}

/**
 * À ajouter à la fin de ton main() :
 * 
 * int main(void)
 * {
 *     t_vars v;
 *     // ... ton code ...
 *     
 *     cleanup_all_textures(&v);
 *     return (0);
 * }
 * 
 * Et dans tes exit() d'erreur :
 * 
 * if (erreur)
 * {
 *     emergency_cleanup(&v);
 *     exit(EXIT_FAILURE);
 * }
 */

 void cleanup_all(t_vars *v)
{
    if (v->t_map.map)
        free_tab(v->t_map.map);
    if (v->coin)
        free(v->coin);
    if (v->mob)
        free(v->mob);
    cleanup_all_textures(v);
}