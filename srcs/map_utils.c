/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:06:36 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/03 13:34:36 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_ff(char **map, char **clonemap, char **clonemap2, t_vars *v)
{
	free_tab(map);
	free_tab(clonemap);
	free_tab(clonemap2);
	free(v);
	ft_putstr_fd("Error\nFloodFill invalid.\n", 2);
	exit(EXIT_FAILURE);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	error_map(char **map, t_vars *v)
{
	free_tab(map);
	free(v);
	ft_putstr_fd("Error\nMap invalid.\n", 2);
	exit(EXIT_FAILURE);
}

int	count_element(char **map, char element)
{
	int	i;
	int	y;
	int	count;

	count = 0;
	i = 0;
	y = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] == element)
				count++;
			y++;
		}
		i++;
	}
	return (count);
}

void	free_tab(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
