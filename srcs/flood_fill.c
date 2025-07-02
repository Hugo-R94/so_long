/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:07:43 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 17:42:21 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	flood_fill_element(char **map, int x, int y, char element)
{
	int	count;

	count = 0;
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == element)
		count = 1;
	map[y][x] = 'V';
	count += flood_fill_element(map, x + 1, y, element);
	count += flood_fill_element(map, x - 1, y, element);
	count += flood_fill_element(map, x, y + 1, element);
	count += flood_fill_element(map, x, y - 1, element);
	return (count);
}

static char	**allocate_clone(char **map)
{
	char	**new_map;
	int		i;
	int		j;

	i = 0;
	while (map[i])
		i++;
	new_map = malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		new_map[i] = malloc(sizeof(char) * (j + 1));
		if (!new_map[i])
			return (NULL);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

char	**clone_map(char **map)
{
	char	**new_map;
	int		i;
	int		j;

	new_map = allocate_clone(map);
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	return (new_map);
}

void	find_player(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	check_path(char **map)
{
	char	**checkmap;
	char	**checkmap2;
	int		px;
	int		py;
	int		nb_c;

	nb_c = count_element(map, 'C');
	checkmap = clone_map(map);
	checkmap2 = clone_map(map);
	find_player(map, &px, &py);
	if (flood_fill_element(checkmap, px, py, 'E') != 1)
		error_ff(map, checkmap);
	if (flood_fill_element(checkmap2, px, py, 'C') != nb_c)
		error_ff(map, checkmap2);
	free_tab(checkmap);
	free_tab(checkmap2);
	return ;
}
