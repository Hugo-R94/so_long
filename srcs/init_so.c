/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_so.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:23 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/18 17:44:58 by hrouchy          ###   ########.fr       */
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
	v->tile_size = 100;
	v->t_map.height_px = rows * v->tile_size;
	v->t_map.width_px = cols * v->tile_size;
	// if (tile_h > tile_w) //a integrer plus tard
	// 	ret = tile_h;
	// else
	// 	ret = tile_w;
	// if (ret < 500 && ret >= 250)
	// 	v->tile_size = 250;
	// else if (tile_h < 250)
	// 	v->tile_size = 125;
	// else
	// 	v->tile_size = 500;
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
	v->moving = 0;
}
// calculate_map_px_size(t_vars *v)
// {
// 	int	map_size;
	
// 	map_size = v->tile_size *v->
// }
// void load_texture(t_my_img *img, void *mlx, char *path)
// {
// 	int w, h;
// 	img->img_ptr = mlx_xpm_file_to_image(mlx, path, &w, &h);
// 	if (!img->img_ptr)
// 	{
// 		ft_putendl_fd("Erreur chargement image", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	img->width = w;
// 	img->height = h;
// 	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_length, &img->endian);
// }


void	init_texture(t_vars *v)
{
	int			size;

	size = v->tile_size;
	v->tx.wall = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/wall.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: wall.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.ground = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/ground.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: ground.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.coin = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/coin_0.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: coin.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.player = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/player.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: hulk_still.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
	v->tx.exit = mlx_xpm_file_to_image(v->mlx, "placeholder_assets/exit.xpm", &size, &size);
	if (!v->tx.wall)
	{
		ft_putendl_fd("Erreur: exit.xpm non chargé", 2);
		exit(EXIT_FAILURE);
	}
}

// void	init_my_img(t_my_img *img)
// {
// 	img->img_ptr = NULL;
// 	img->addr = NULL;
// 	img->bpp = 0;
// 	img->line_length = 0;
// 	img->endian = 0;
// 	img->width = 0;
// 	img->height = 0;
// }
// void	init_all_textures(t_texture *tx)
// {
// 	init_my_img(&tx->wall);
// 	init_my_img(&tx->ground);
// 	init_my_img(&tx->coin);
// 	init_my_img(&tx->player);
// 	init_my_img(&tx->exit);
// }

// void	init_texture(t_vars *v)
// {
// 	load_texture(&v->tx.wall, v->mlx, "placeholder_assets/wall.xpm");
// 	load_texture(&v->tx.ground, v->mlx, "placeholder_assets/ground.xpm");
// 	load_texture(&v->tx.coin, v->mlx, "placeholder_assets/coin_0.xpm");
// 	load_texture(&v->tx.player, v->mlx, "placeholder_assets/player.xpm");
// 	load_texture(&v->tx.exit, v->mlx, "placeholder_assets/exit.xpm");
// }

// void	init_texture(t_vars *v)
// {
// 	load_texture(&v->tx.wall, v->mlx, "placeholder_assets/wall.xpm");
// 	if (!v->tx.wall.img_ptr)
// 	{
// 		ft_putendl_fd("Erreur: wall.xpm non chargé", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	load_texture(&v->tx.ground, v->mlx,"placeholder_assets/ground.xpm");
// 	if (!v->tx.ground.img_ptr)
// 	{
// 		ft_putendl_fd("Erreur: ground.xpm non chargé", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	load_texture(&v->tx.coin, v->mlx, "placeholder_assets/coin_0.xpm");
// 	if (!v->tx.coin.img_ptr)
// 	{
// 		ft_putendl_fd("Erreur: coin.xpm non chargé", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	load_texture(&v->tx.player, v->mlx, "placeholder_assets/player.xpm");
// 	if (!v->tx.player.img_ptr)
// 	{
// 		ft_putendl_fd("Erreur: hulk_still.xpm non chargé", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	load_texture(&v->tx.exit, v->mlx, "placeholder_assets/exit.xpm");
// 	if (!v->tx.exit.img_ptr)
// 	{
// 		ft_putendl_fd("Erreur: exit.xpm non chargé", 2);
// 		exit(EXIT_FAILURE);
// 	}
// }

void	get_exit(t_vars *v)
{
	int x;
	int	y;
	
	x = 0;;
	y = 0;
	while (v->t_map.map[x])
	{
		y = 0;
		while (v->t_map.map[x][y])
		{
			
			if (v->t_map.map[x][y] == 'E')
			{
				v->exit.ex = x;
				v->exit.ey = y;
				v->exit.open = 0;
			}	
			y++;
		}
		x++;
	}
	
}

void	render_background(t_vars *v)
{
	int	i;
	int j;
	int draw_x;
	int draw_y;

	i = 0;
	while (v->t_map.map[i])
	{
		j = 0;
		while (v->t_map.map[i][j])
		{
			draw_x = (j * v->tile_size) - (int)v->t_cam.x;
			draw_y = (i * v->tile_size) - (int)v->t_cam.y;

			if (v->t_map.map[i][j] == '1')
				mlx_put_image_to_window(v->mlx, v->win, v->tx.wall, draw_x, draw_y);
			else if (v->t_map.map[i][j] == 'E')
				mlx_put_image_to_window(v->mlx, v->win, v->tx.exit, draw_x, draw_y);
			else if (v->t_map.map[i][j] != '\n')
				mlx_put_image_to_window(v->mlx, v->win, v->tx.ground, draw_x, draw_y);

			j++;
		}
		i++;
	}
}
