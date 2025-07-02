/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:55:11 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 13:01:44 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	emergency_cleanup_sub2(t_vars *v)
{
	if (v->opt_txt.jump)
	{
		free(v->opt_txt.jump);
		v->opt_txt.jump = NULL;
	}
	if (v->opt_txt.jump_r)
	{
		free(v->opt_txt.jump_r);
		v->opt_txt.jump_r = NULL;
	}
	if (v->opt_txt.mob)
	{
		free(v->opt_txt.mob);
		v->opt_txt.mob = NULL;
	}
	if (v->opt_txt.placeholder)
	{
		free(v->opt_txt.placeholder);
		v->opt_txt.placeholder = NULL;
	}
}

void	emergency_cleanup_sub1(t_vars *v)
{
	if (v->opt_txt.ground)
	{
		free(v->opt_txt.ground);
		v->opt_txt.ground = NULL;
	}
	if (v->opt_txt.coin)
	{
		free(v->opt_txt.coin);
		v->opt_txt.coin = NULL;
	}
	if (v->opt_txt.exit)
	{
		free(v->opt_txt.exit);
		v->opt_txt.exit = NULL;
	}
	if (v->opt_txt.shadow)
	{
		free(v->opt_txt.shadow);
		v->opt_txt.shadow = NULL;
	}
	emergency_cleanup_sub2(v);
}
