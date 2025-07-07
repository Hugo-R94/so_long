/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:03:45 by hugz              #+#    #+#             */
/*   Updated: 2025/07/04 11:39:17 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clean_except_optimized(t_vars *v)
{
	if (!v)
		return ;
	cleanup_mlx_textures(v);
	cleanup_frame(v);
	free_vars_resources(v);
	free_tab(v->t_map.map);
	free(v);
	exit(EXIT_FAILURE);
}

void	check_texture(t_vars *v)
{
	t_texture	*txt;

	txt = &v->tx;
	if (!txt->player[0].image || !txt->player[1].image || !txt->player[2].image
		|| !txt->player[3].image || !txt->player[4].image
		|| !txt->player[5].image || !txt->ground.image
		|| !txt->coin.image || !txt->exit.image
		|| !txt->shadow.image || !v->overlay
		|| !txt->wall.top.image || !txt->wall.bottom.image
		|| !txt->wall.left.image || !txt->wall.right.image
		|| !txt->wall.corner_tl.image || !txt->wall.corner_tr.image
		|| !txt->wall.corner_bl.image || !txt->wall.corner_br.image
		|| !txt->wall.middle.image
		|| !txt->jump.image || !txt->mob.image || !txt->placeholder.image)
	{
		ft_putendl_fd("Error\nFailed to load one or more textures.", 2);
		clean_except_optimized(v);
		exit(EXIT_FAILURE);
	}
}
