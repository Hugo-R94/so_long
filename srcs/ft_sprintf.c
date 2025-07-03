/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:58:49 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/03 13:34:28 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdarg.h>
#include <stdlib.h>

static int	handle_percent_i(char *res, int j, va_list args)
{
	char	*tmp;
	int		k;

	tmp = ft_itoa(va_arg(args, int));
	if (!tmp)
		return (j);
	k = 0;
	while (tmp[k])
		res[j++] = tmp[k++];
	free(tmp);
	return (j);
}

char	*ft_sprintf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		j;
	char	*res;

	res = malloc(sizeof(char) * 100);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 'i')
		{
			j = handle_percent_i(res, j, args);
			i += 2;
		}
		else
			res[j++] = format[i++];
	}
	res[j] = '\0';
	va_end(args);
	return (res);
}

void	error_exit(t_vars *vars)
{
	if (vars)
	{
		if (vars->img)
			mlx_destroy_image(vars->mlx, vars->img);
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		if (vars->mlx)
			free(vars->mlx);
		if (vars->t_map.map)
			free_tab(vars->t_map.map);
	}
	ft_putstr_fd("Error\n Vars initialisation issue.", 2);
	exit(EXIT_FAILURE);
}
