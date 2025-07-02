/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:49:28 by hugz              #+#    #+#             */
/*   Updated: 2025/07/02 12:04:08 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <string.h>

char set_wall(char **map, int y, int x, int rows, int cols)
{
    if (map[y][x] != '1')
        return map[y][x];
    if (y == 0 && x == 0)
        return 'A';  // coin haut gauche
    if (y == 0 && x == cols - 2)
        return 'Z';  // coin haut droit
    if (y == rows - 1 && x == 0)
        return 'O';  // coin bas gauche
    if (y == rows - 1 && x == cols - 2)
        return 'D';  // coin bas droit
    if (y == 0)
        return 'T';  // mur top
    if (y == rows - 1)
        return 'B';  // mur bottom
    if (x == 0)
        return 'L';  // mur left
    if (x == cols - 2)
        return 'R';  // mur right
    return '1';
}

static char *remap_line(char **map, int y, int cols, int rows)
{
    char *new_line;
    int x;

    new_line = malloc(sizeof(char) * (cols + 1));
    if (!new_line)
        return NULL;
    x = 0;
    while (x < cols)
    {
        if (map[y][x] == '1')
            new_line[x] = set_wall(map, y, x, rows, cols);
        else
            new_line[x] = map[y][x];
        x++;
    }
    new_line[cols] = '\0';
    return new_line;
}

char **remap(char **map)
{
    int rows;
    int cols;
    char **new_map;
    int y;

    rows = 0;
    while (map[rows])
        rows++;
    cols = strlen(map[0]);
    new_map = malloc(sizeof(char *) * (rows + 1));
    if (!new_map)
        return NULL;
    y = 0;
    while (y < rows)
    {
        new_map[y] = remap_line(map, y, cols, rows);
        if (!new_map[y])
            return NULL;
        y++;
    }
    new_map[rows] = NULL;
    free_tab(map);
    return new_map;
}
