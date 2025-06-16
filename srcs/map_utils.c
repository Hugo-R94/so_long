/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:06:36 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/16 11:44:23 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"


void	error_ff(char **map, char **clonemap)
{
	free(map);
	free(clonemap);
	printf("Error floodfill impossible");
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

void	error_map(char **map)
{
	free(map);
	printf("Error map invalid.\n");
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
	while (map[i])
		i++;
	while (i >= 0)
		free(map[i--]);
	free(map);
}
