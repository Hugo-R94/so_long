/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:13 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/16 11:13:22 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	check_path(char **map);

static int	check_horizontal_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
			return (-1);
		i++;
	}
	return (i);
}

static int	check_vertical_wall(char **map, int col_index)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][col_index] != '1')
			return (-1);
		i++;
	}
	return (i);
}

static int	check_wall(char **map)
{
	int	height;
	int	top_len;
	int	bottom_len;
	int	left_height;
	int	right_height;

	if (!map || !map[0])
		return (-1);
	top_len = check_horizontal_wall(map[0]);
	height = 0;
	while (map[height])
		height++;
	bottom_len = check_horizontal_wall(map[height - 1]);
	if (top_len == -1 || bottom_len == -1 || bottom_len != top_len)
	{
		return (-1);
	}
	left_height = check_vertical_wall(map, 0);
	right_height = check_vertical_wall(map, top_len - 1);
	if (left_height == -1 || right_height == -1 || left_height != right_height)
	{
		return (-1);
	}
	return (1);
}

int	check_invalid(char **map)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] != '1' && map[i][y] != 'C' && map[i][y] != '0' &&
				map[i][y] != 'E' && map[i][y] != 'P' && map[i][y] != '\n')
				return (-1);
			y++;
		}
		i++;
	}
	return (1);
}

void	check_map(char **map)
{
	int	p_count;
	int	c_count;
	int	e_count;

	p_count = count_element(map, 'P');
	c_count = count_element(map, 'C');
	e_count = count_element(map, 'E');
	check_invalid(map);
	if (p_count != 1 || e_count != 1 || c_count < 1
		|| check_wall(map) == -1 || check_invalid(map) == -1)
		error_map(map);
	check_path(map);
	printf("Map valide.\n");
	return ;
}
