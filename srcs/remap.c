/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:49:28 by hugz              #+#    #+#             */
/*   Updated: 2025/07/02 15:36:17 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <string.h>

char	set_wall(char **map, int y, int x, int *bounds)
{
	if (map[y][x] != '1')
		return (map[y][x]);
	if (y == 0 && x == 0)
		return ('A');
	if (y == 0 && x == bounds[1] - 2)
		return ('Z');
	if (y == bounds[0] - 1 && x == 0)
		return ('O');
	if (y == bounds[0] - 1 && x == bounds[1] - 2)
		return ('D');
	if (y == 0)
		return ('T');
	if (y == bounds[0] - 1)
		return ('B');
	if (x == 0)
		return ('L');
	if (x == bounds[1] - 2)
		return ('R');
	return ('1');
}

static char	*remap_line(char **map, int y, int cols, int rows)
{
	char	*new_line;
	int		x;
	int		bounds[2];

	bounds[0] = rows;
	bounds[1] = cols;
	new_line = malloc(sizeof(char) * (cols + 1));
	if (!new_line)
		return (NULL);
	x = 0;
	while (x < cols)
	{
		if (map[y][x] == '1')
			new_line[x] = set_wall(map, y, x, bounds);
		else
			new_line[x] = map[y][x];
		x++;
	}
	new_line[cols] = '\0';
	return (new_line);
}

char	**remap(char **map)
{
	int		rows;
	int		cols;
	char	**new_map;
	int		y;

	rows = 0;
	while (map[rows])
		rows++;
	cols = strlen(map[0]);
	new_map = malloc(sizeof(char *) * (rows + 1));
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < rows)
	{
		new_map[y] = remap_line(map, y, cols, rows);
		if (!new_map[y])
			return (NULL);
		y++;
	}
	new_map[rows] = NULL;
	free_tab(map);
	return (new_map);
}
