/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_old.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:41:52 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/18 11:03:44 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_player {
	double x;       // position logique (en tuiles mais flottant)
	double y;
	int    pixel_x; // position réelle à l’écran (en pixels)
	int    pixel_y;
	void  *img;
} t_player;

// int key_handler_p(int keycode, t_player player)
// {
// 	if (keycode == 32)
// 	{
// 		printf("SPACE");
		
// 	}
//     else if (keycode == 97 || keycode == 65361)
// 	{
// 		player.y -= 0.2; 
//         ft_printf("LEFT (A / ARROW_LEFT)\n");
// 	}
//     else if (keycode == 100 || keycode == 65363)
// 	{
// 		player.y += 0.2; 
//         ft_printf("RIGHT (D / ARROW_RIGHT)\n");
// 	}
//     else if (keycode == 115 || keycode == 65364)
// 	{
// 		player.x -= 0.2; 
//         ft_printf("DOWN (S / ARROW_DOWN)\n");
// 	}
//     else if (keycode == 119 || keycode == 65362)
//      {
// 		player.x += 0.2; 
// 		ft_printf("UP (W / ARROW_UP)\n");
// 	 }
//     else
//        ft_printf("%d\n", keycode);
//     return (0);
// }
#include <stdio.h>

void get_player_abs_pos(char **map, double *px, double *py)
{
	int y = 0;
	while (map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				printf("%i | %i\n",x,y);
				*px = (double)x;
				*py = (double)y;
				return;
			}
			x++;
		}
		y++;
	}
}



	void render_player(void *mlx_ptr,void *win_ptr, char **map)
	{
		int			width;
		int			height;
		
		
		width = 100;
		height = 100;
		t_player player;
		int tile_size;
		int	offset_x;
		int	offset_y;
		get_player_abs_pos(map, &player.x, &player.y);
		player.img = mlx_xpm_file_to_image(mlx_ptr, "placeholder_assets/player.xpm", &height, &width);
		tile_size = calculate_tile_size(1920, 1080, map);
		printf("t_size %i\n",tile_size);

		calculate_offset(1920, 1080, map, tile_size, &offset_x, &offset_y);
		player.pixel_x = player.x * tile_size;
		player.pixel_y = player.y * tile_size;
		printf("player_px = %i | player_py = %i\n",player.pixel_x + offset_x, player.pixel_y);
		mlx_put_image_to_window(mlx_ptr,win_ptr,player.img, player.pixel_x + offset_x,player.pixel_y + offset_y);
	}	