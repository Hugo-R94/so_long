/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:21:26 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/18 14:31:16 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_coin_count(t_vars *vars)
{
	int i;
	int j;
	int count;
	
	i = 0;
	count = 0;
	while (vars->t_map.map[i])
	{
		j = 0;
		while (vars->t_map.map[i][j])
		{
			if (vars->t_map.map[i][j] == 'C')
				count++;
			j++;
		}
	i++;
	}
	vars->coin_count = count;
}

void load_coin(t_vars *vars)
{
    int index;
    int i;
    int j;

    vars->coin = malloc(sizeof(t_coin) * vars->coin_count);
    if (!vars->coin)
    {
        ft_printf("Erreur malloc coins\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    index = 0;
    while (vars->t_map.map[i])
    {
        j = 0;
        while (vars->t_map.map[i][j])
        {
            if (vars->t_map.map[i][j] == 'C')
            {
                vars->coin[index].cx = j; // colonne
                vars->coin[index].cy = i; // ligne
				vars->coin[index].vis = 1;
                index++;
            }
            j++;
        }
        i++;
    }
}

void	init_coins(t_vars *v)
{
	int i;
	
	i = 0;
	get_coin_count(v);
	load_coin(v);
	v->coin_get = 0;
}

void render_coin(t_vars *v, t_coin *coin)
{
	if (!v->tx.coin || !coin->vis)
		return;

	int cx = (coin->cx * v->tile_size ) - (int)v->t_cam.x;
	int cy = (coin->cy * v->tile_size) - (int)v->t_cam.y;

	mlx_put_image_to_window(v->mlx, v->win, v->tx.coin, cx, cy);
}
