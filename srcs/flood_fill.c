/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:03:30 by hugz              #+#    #+#             */
/*   Updated: 2025/06/15 13:59:39 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../My_libft/headers/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	count_element(char **map, char element);

void free_tab(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	while (i >= 0)
		free(map[i--]);
	free(map);
}

void	error_ff(char **map, char **clonemap)
{
	free(map);
	free(clonemap);
	printf("Error floodfill impossible");
	exit(EXIT_FAILURE);
}


int flood_fill_element(char **map, int x, int y, char element)
{
	int count;

	count = 0;
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return (0);

	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == element)
		count = 1;
	map[y][x] = 'V';
	count += flood_fill_element(map, x + 1, y, element); // droite
	count += flood_fill_element(map, x - 1, y, element); // gauche
	count += flood_fill_element(map, x, y + 1, element); // bas
	count += flood_fill_element(map, x, y - 1, element); // haut
	return (count);
}



char **clone_map(char **map)
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
		j = 0;
		while (map[i][j])
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

void find_player(char **map, int *x, int *y)
{
    int i = 0, j;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
                *x = j;
                *y = i;
                return;
            }
            j++;
        }
        i++;
    }
}


void check_path(char **map)
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