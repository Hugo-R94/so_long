/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:13 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/15 14:06:35 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

void check_path(char **map);

static void	error_map(char **map)
{
	free(map);
	printf("Error map invalid.\n");
	exit(EXIT_FAILURE);
}

int	count_element(char **map, char element)
{
	int i;
	int	y;
	int count;

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
	return(count);
}

static int	check_horizontal_wall(char *line)
{
	int i = 0;

	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
			return -1;
		i++;
	}
	return i;
}

static int	check_vertical_wall(char **map, int col_index)
{
	int i = 0;

	while (map[i])
	{
		if (map[i][col_index] != '1')
			return -1;
		i++;
	}
	return i;
}

static int	check_wall(char **map)
{
	int height;
	int top_len;
	int bottom_len;
	int left_height;
	int right_height;

	if (!map || !map[0])
		return -1;
	top_len = check_horizontal_wall(map[0]);
	height = 0;
	while (map[height])
		height++;
	bottom_len = check_horizontal_wall(map[height - 1]);
	if (top_len == -1 || bottom_len == -1 || bottom_len != top_len)
	{
		return -1;
	}
	left_height = check_vertical_wall(map, 0);
	right_height = check_vertical_wall(map, top_len - 1);
	if (left_height == -1 || right_height == -1 || left_height != right_height)
	{
		return -1;
	}
	return 1;
}
int	check_invalid(char **map)
{
	int i;
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
	return(1);
}



void	check_map(char **map)
{
	int P_count;
	int	C_count;
	int	E_count;

	P_count = count_element(map, 'P');
	C_count = count_element(map, 'C');
	E_count = count_element(map, 'E');
	check_invalid(map);
	//printf("Pcount = %i | Ccount = %i | Ecount = %i\n",P_count, C_count, E_count);
	if (P_count != 1 || E_count != 1 || C_count < 1 || check_wall(map) == -1 || check_invalid(map) == -1)
		error_map(map);
	check_path(map);
	printf("Map valide.\n");
	return ;
}