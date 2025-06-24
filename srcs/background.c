/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:23:24 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/24 16:24:35 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_tile_size_n_mapsize(t_vars *v)
{
	int	rows = 0;
	int	cols = 0;
	
	while (v->t_map.map[rows])
	{
		cols = 0;
		while (v->t_map.map[rows][cols])
			cols++;
		rows++;
	}
	v->tile_size = 200;
	v->t_map.height_px = rows * v->tile_size;
	v->t_map.width_px = cols * v->tile_size;
	return 0;
}

void	calculate_offset(t_vars *v)
{
	int	rows = 0;
	int	cols = 0;
	int x_map_size;
	int y_map_size;
	
	while (v->t_map.map[rows])
	{
		cols = 0;
		while (v->t_map.map[rows][cols])
			cols++;
		rows++;
	}
	x_map_size = cols * v->tile_size;
	y_map_size = rows * v->tile_size;
	v->offset_x = (RES_X - x_map_size)/2;
	v->offset_y = (RES_Y- y_map_size)/2;
	v->t_map.map_rows = rows;
	v->t_map.map_cols = cols;
	v->moving = 0;
}

// void draw_x_wall(t_img *dst, t_vars *v, int x, int y)
// {
// 	int draw_x = (y * v->tile_size) - (int)v->t_cam.x;
// 	int draw_y = (x * v->tile_size) - (int)v->t_cam.y;

// 	int rows = v->t_map.map_rows;
// 	int cols = v->t_map.map_cols;

// 	if ((x + 1 < rows && y + 1 < cols && v->t_map.map[x + 1][y] == '1' && v->t_map.map[x][y + 1] == '1') ||
// 		(x - 1 >= 0 && y + 1 < cols && v->t_map.map[x - 1][y] == '1' && v->t_map.map[x][y + 1] == '1') ||
// 		(x - 1 >= 0 && y - 1 >= 0 && v->t_map.map[x - 1][y] == '1' && v->t_map.map[x][y - 1] == '1') ||
// 		(x + 1 < rows && y - 1 >= 0 && v->t_map.map[x + 1][y] == '1' && v->t_map.map[x][y - 1] == '1'))
// 	{
// 		draw_image(dst, &v->tx.wall.corner, draw_x, draw_y);
// 	}
// 	else if (x == 0)
// 		draw_image(dst, &v->tx.wall.top, draw_x, draw_y);
// 	else if (x == rows - 1)
// 		draw_image(dst, &v->tx.wall.bottom, draw_x, draw_y);
// 	else if (y == 0)
// 		draw_image(dst, &v->tx.wall.left, draw_x, draw_y);
// 	else if (y == cols - 1)
// 		draw_image(dst, &v->tx.wall.right, draw_x, draw_y);
// 	else
// 		draw_image(dst, &v->tx.wall.middle, draw_x, draw_y); // 💺 Chaise pliante ici
// }

// unsigned int draw_pixel_wall(t_vars *v, int px, int py, int ty, int tx)
// {
// 	int up    = (ty > 0) && (v->t_map.map[ty - 1][tx] == '1');
// 	int down  = (ty < v->t_map.map_rows - 1) && (v->t_map.map[ty + 1][tx] == '1');
// 	int left  = (tx > 0) && (v->t_map.map[ty][tx - 1] == '1');
// 	int right = (tx < v->t_map.map_cols - 1) && (v->t_map.map[ty][tx + 1] == '1');

// 	uint32_t *tex = NULL;

// 	if (!up && down && left && right)
// 		tex = v->opt_txt.wall[0]; // TOP
// 	else if (up && !down && left && right)
// 		tex = v->opt_txt.wall[1]; // BOTTOM
// 	else if (up && down && !left && right)
// 		tex = v->opt_txt.wall[2]; // LEFT
// 	else if (up && down && left && !right)
// 		tex = v->opt_txt.wall[3]; // RIGHT
// 	else if ((up && left && !down && !right) || (down && right && !up && !left))
// 		tex = v->opt_txt.wall[4]; // CORNER
// 	else
// 		tex = v->opt_txt.wall[5]; // MIDDLE par défaut
// 	printf("TEX: ");
// 	if (tex == v->opt_txt.wall[0]) printf("top\n");
// 	else if (tex == v->opt_txt.wall[1]) printf("bottom\n");
// 	else if (tex == v->opt_txt.wall[2]) printf("left\n");
// 	else if (tex == v->opt_txt.wall[3]) printf("right\n");
// 	else if (tex == v->opt_txt.wall[4]) printf("corner\n");
// 	else if (tex == v->opt_txt.wall[5]) printf("middle\n");
// 	else printf("inconnu\n");

// 	if (tex == NULL)
// 	{
// 		printf("ERREUR: texture mur NULL à (%d,%d)\n", tx, ty);
// 		return 0xFF00FF; // rose flashy
// 	}

// 	return tex[py * v->tile_size + px];
// }


// //MARCHEE
// void draw_pixel_background(t_vars *v, int px, int py)
// {
//     int top = (int)v->player.view_y - 3;
//     int bottom = (int)v->player.grid_y + 3;
//     int left = (int)v->player.grid_x - 6;
//     int right = (int)v->player.grid_x + 6;

//     if (top < 0) top = 0;
//     if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
//     if (left < 0) left = 0;
//     if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;

//     for (int ty = top; ty <= bottom; ty++)
//     {
//         for (int tx = left; tx <= right; tx++)
//         {
//             int draw_x = (tx * v->tile_size) - (int)v->t_cam.x + px;
//             int draw_y = (ty * v->tile_size) - (int)v->t_cam.y + py;

//             char tile = v->t_map.map[ty][tx];
//             unsigned int color = 0x000000;
			
//             if (tile == '1')
// 			{
// 				if (!v->opt_txt.wall)
// 					printf("c dla merde");
// 				if (px < 0 || px >= v->tile_size || py < 0 || py >= v->tile_size) {
// 					printf("Erreur: px ou py hors limites px=%d py=%d\n", px, py);
// 					return;
// 				}
// 				printf("BP\n");	
//                 color = v->opt_txt.wall[py * v->tile_size + px];
// 			}

//             else if (tile == 'E')			
//                 color = v->opt_txt.exit[py * v->tile_size + px];
//             else
//                 color = v->opt_txt.ground[py * v->tile_size + px];

//             if (color != 0x000000)
//                 put_pixel(v->frame.image, draw_x, draw_y, color);
			
//         }
//     }
// }

void draw_pixel_background(t_vars *v, int px, int py)
{
    int top = (int)v->player.view_y - 3;
    int bottom = (int)v->player.grid_y + 3;
    int left = (int)v->player.grid_x - 6;
    int right = (int)v->player.grid_x + 6;

    if (top < 0) top = 0;
    if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
    if (left < 0) left = 0;
    if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;

    int ty = top;
    while (ty <= bottom)
    {
        int tx = left;
        while (tx <= right)
        {
            int draw_x = (tx * v->tile_size) - (int)v->t_cam.x + px;
            int draw_y = (ty * v->tile_size) - (int)v->t_cam.y + py;

            char tile = v->t_map.map[ty][tx];
            unsigned int color = 0x000000;
			if (is_wall(tile))
			{
				if (tile == 'T')       // Top
					color = v->opt_txt.wall[0][py * v->tile_size + px];
				else if (tile == 'B')  // Bottom
					color = v->opt_txt.wall[1][py * v->tile_size + px];
				else if (tile == 'L')  // Left
					color = v->opt_txt.wall[2][py * v->tile_size + px];
				else if (tile == 'R')  // Right
					color = v->opt_txt.wall[3][py * v->tile_size + px];
				else if (tile == 'O')
					color = v->opt_txt.wall[6][py * v->tile_size + px];
				else if (tile == 'A')
					color = v->opt_txt.wall[4][py * v->tile_size + px];
				else if (tile == 'Z')
					color = v->opt_txt.wall[5][py * v->tile_size + px];
				else if (tile == 'D')
					color = v->opt_txt.wall[7][py * v->tile_size + px];
				else                   
					color = v->opt_txt.wall[8][py * v->tile_size + px];
			}
			// if (is_wall(tile))
			// {
			// 	color = v->opt_txt.coin[py * v->tile_size + px];
			// }
            // if (tile == 'A' || tile == 'M' || tile == 'O' || tile == 'D' || tile == 'T' || tile == 'B' || tile == 'R' || tile == 'L')
			// 	color = v->opt_txt.wall[3][py * v->tile_size + px]; // test simple
			// //	color = draw_pixel_wall(v, px, py, ty, tx);
            // //    color = v->opt_txt.wall[py * v->tile_size + px];
            else if (tile == 'E')
            {
				color = v->opt_txt.ground[py * v->tile_size + px];
				put_pixel(v->frame.image, draw_x, draw_y, color);
				color = v->opt_txt.exit[py * v->tile_size + px];
			}
            else
                color = v->opt_txt.ground[py * v->tile_size + px];

			if (color != 0x000000)
				put_pixel(v->frame.image, draw_x, draw_y, color);
            tx++;
        }
        ty++;
    }
}




void	get_exit(t_vars *v)
{
	int x;
	int	y;
	
	x = 0;
	y = 0;
	while (v->t_map.map[x])
	{
		y = 0;
		while (v->t_map.map[x][y])
		{
			if (v->t_map.map[x][y] == 'E')
			{
				v->exit.ex = y;
				v->exit.ey = x;
				v->exit.open = 0;
			}
			y++;
		}
		x++;
	}
	
}
// t_img *get_wall_texture(t_vars *v, int x, int y)
// {
// 	int rows = v->t_map.map_rows;
// 	int cols = v->t_map.map_cols;

// 	if ((x + 1 < rows && y + 1 < cols && v->t_map.map[x + 1][y] == '1' && v->t_map.map[x][y + 1] == '1') ||
// 		(x - 1 >= 0 && y + 1 < cols && v->t_map.map[x - 1][y] == '1' && v->t_map.map[x][y + 1] == '1') ||
// 		(x - 1 >= 0 && y - 1 >= 0 && v->t_map.map[x - 1][y] == '1' && v->t_map.map[x][y - 1] == '1') ||
// 		(x + 1 < rows && y - 1 >= 0 && v->t_map.map[x + 1][y] == '1' && v->t_map.map[x][y - 1] == '1'))
// 	{
// 		return &v->tx.wall.corner;
// 	}
// 	else if (x == 0)
// 		return &v->tx.wall.top;
// 	else if (x == rows - 1)
// 		return &v->tx.wall.bottom;
// 	else if (y == 0)
// 		return &v->tx.wall.left;
// 	else if (y == cols - 1)
// 		return &v->tx.wall.right;
// 	else
// 		return &v->tx.wall.middle; // 🪑 ici aussi la chaise pliante
// }

// void draw_pixel_background(t_vars *v, int x, int y)
// {
// 	int i = 0;
// 	while (v->t_map.map[i])
// 	{
// 		int j = 0;
// 		while (v->t_map.map[i][j])
// 		{
// 			char tile = v->t_map.map[i][j];
// 			if (tile == '\n')
// 			{
// 				j++;
// 				continue;
// 			}

// 			t_img *tex = NULL;
// 			if (tile == '1')
// 				tex = get_wall_texture(v, i, j);
// 			else if (tile == 'E')
// 				tex = &v->tx.exit;
// 			else
// 				tex = &v->tx.ground;

// 			if (!tex || !tex->image)
// 			{
// 				j++;
// 				continue;
// 			}

// 			// Attention ici : draw_x/y décalés une seule fois par tile
// 			int draw_x = (j * v->tile_size) - (int)v->t_cam.x;
// 			int draw_y = (i * v->tile_size) - (int)v->t_cam.y;

// 			// Et là tu viens ajouter le pixel local x/y
// 			unsigned int color = get_pixel(tex, x, y);
// 			if (color != 0x000000)
// 				put_pixel(v->frame.image, draw_x + x, draw_y + y, color);

// 			j++;
// 		}
// 		i++;
// 	}
// }


///worksssHERE
// void draw_pixel_background(t_vars *v, int px, int py)
// {
//     int top = (int)v->player.view_y  - 3;
//     int bottom = (int)v->player.grid_y + 3;
//     int left = (int)v->player.grid_x - 6;
//     int right = (int)v->player.grid_x + 6;

//     if (top < 0) top = 0;
//     if (bottom >= v->t_map.map_rows) bottom = v->t_map.map_rows - 1;
//     if (left < 0) left = 0;
//     if (right >= v->t_map.map_cols) right = v->t_map.map_cols - 1;
// 	//printf("top = %i | bot = %i | left = %i | right = %i\n",top,bottom,left,right);
//     // On boucle sur toutes les tiles visibles
//     for (int ty = top; ty <= bottom; ty++)
//     {
//         for (int tx = left; tx <= right; tx++)
//         {
//             // Calcul de la position en pixels sur l’écran de ce pixel particulier (px, py) dans la tile (tx, ty)
//             int draw_x = (tx * v->tile_size) - (int)v->t_cam.x + px;
//             int draw_y = (ty * v->tile_size) - (int)v->t_cam.y + py;

//             // Vérifie que le pixel à dessiner correspond bien à celui que l'on veut (px, py)
//             // Ici c’est implicite car on boucle sur les tiles, puis chaque pixel est appelé par la boucle externe

//             char tile = v->t_map.map[ty][tx];
//             unsigned int color = 0x000000;

//             if (tile == '1')
//                 color = get_pixel(&v->tx.wall, px, py);
//             else if (tile == 'E')
//                 color = get_pixel(&v->tx.exit, px, py);
//             else 
//                 color = get_pixel(&v->tx.ground, px, py);

//             if (color != 0x000000)
//                 put_pixel(v->frame.image, draw_x, draw_y, color);
//         }
//     }
// }



	//printf("sorti dans pixel bgg \n");




// while (v->t_map.map[i][j])
// 		{
// 			char tile = v->t_map.map[i][j];
// 			if (tile == '\n')
// 			{
// 				j++;
// 				continue;
// 			}

// 			t_img *tex = NULL;
// 			if (tile == '1')
// 				tex = get_wall_texture(v, i, j);
// 			else if (tile == 'E')
// 				tex = &v->tx.exit;
// 			else
// 				tex = &v->tx.ground;

// 			if (!tex || !tex->image)
// 			{
// 				j++;
// 				continue;
// 			}

// 			// Attention ici : draw_x/y décalés une seule fois par tile
// 			int draw_x = (j * v->tile_size) - (int)v->t_cam.x;
// 			int draw_y = (i * v->tile_size) - (int)v->t_cam.y;

// 			// Et là tu viens ajouter le pixel local x/y
// 			unsigned int color = get_pixel(tex, x, y);
// 			if (color != 0x000000)
// 				put_pixel(v->frame.image, draw_x + x, draw_y + y, color);