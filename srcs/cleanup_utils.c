/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:37:47 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 13:01:09 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_all_textures(t_vars *v)
{
	if (!v)
		return ;
	cleanup_optimized_textures(v);
	cleanup_mlx_textures(v);
	cleanup_frame(v);
}

static void	emergency_cleanup_sub(t_vars *v)
{
	int	i;

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
			free(v->opt_txt.p_right[i]);
			v->opt_txt.p_right[1] = NULL;
		}
	}
}

void	emergency_cleanup(t_vars *v)
{
	int	i;

	if (!v)
		return ;
	emergency_cleanup_sub(v);
	i = -1;
	while (++i < 9)
	{
		if (v->opt_txt.wall[i])
		{
			free(v->opt_txt.wall[i]);
			v->opt_txt.wall[i] = NULL;
		}
	}
}

static void	free_vars_resources(t_vars *v)
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
