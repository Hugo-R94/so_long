/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:49:28 by hugz              #+#    #+#             */
/*   Updated: 2025/06/23 13:24:12 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <string.h>

char set_wall(char **map, int y, int x, int rows, int cols)
{
    if (map[y][x] != '1')
        return map[y][x];

    // Coins
    if (y == 0 && x == 0)
        return 'A';  // coin haut gauche
    if (y == 0 && x == cols - 2)
        return 'Z';  // coin haut droit
    if (y == rows - 1 && x == 0)
        return 'O';  // coin bas gauche
    if (y == rows - 1 && x == cols - 2)
        return 'D';  // coin bas droit

    // Bords (hors coins)
    if (y == 0)
        return 'T';  // mur top
    if (y == rows - 1)
        return 'B';  // mur bottom
    if (x == 0)
        return 'L';  // mur left
    if (x == cols - 2)
        return 'R';  // mur right

    // Mur intérieur
    return 'M';
}

char **remap(char **map)
{
    int rows = 0;
    int cols = 0;
    char **new_map;
    int y, x;

    // Calcul du nombre de lignes
    while (map[rows])
        rows++;

    // Largeur de la map (longueur de la première ligne)
    cols = strlen(map[0]);

    // Allocation du tableau de chaînes
    new_map = malloc(sizeof(char *) * (rows + 1));
    if (!new_map)
        return NULL;

    y = 0;
    while (y < rows)
    {
        new_map[y] = malloc(sizeof(char) * (cols + 1));
        if (!new_map[y])
            return NULL;

        x = 0;
        while (x < cols)
        {
            if (map[y][x] == '1')
                new_map[y][x] = set_wall(map, y, x, rows, cols);
            else
                new_map[y][x] = map[y][x];
            x++;
        }
        new_map[y][cols] = '\0';
        y++;
    }
    new_map[rows] = NULL;

    return new_map;
}
