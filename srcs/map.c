/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:13 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/13 19:28:15 by hrouchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../My_libft/headers/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// char	**getmap(int fd)
// {
// 	char **map;
// 	char *line;
// 	int i;
// 	int y;

// 	i = 0;
// 	line = get_next_line(fd, 0);
// 	map = malloc(sizeof(char *)*6);
// 	while (line)
// 	{
// 		map[i] = malloc(sizeof(char)*5000);
// 		y = 0;
// 		while (line[y++])
// 			map[i][y] = line[y];
// 		map[i][y] = '\0';
// 		i++;		
// 		line = get_next_line(fd, 0);
// 	}
// 	printf("%s",map[i-1]);
// 	return (map);
// }
char	*ft_strcpy(char *dest, char *src)
{
	int i;
	
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_realloc(char **map, int size)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < size && map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

char	**getmap(int fd)
{
	char	**map = NULL;
	char	*line;
	int		i = 0;

	line = get_next_line(fd, 0);
	while (line)
	{
		map = ft_realloc(map, i); // agrandir le tableau de pointeurs
		map[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!map[i])
			return (NULL); // gestion d'erreur simple
		ft_strcpy(map[i], line);
		free(line);
		i++;
		line = get_next_line(fd, 0);
	}
	map = ft_realloc(map, i); // ajouter le NULL final
	map[i] = NULL;
	line = get_next_line(fd, 1); // pour free le buffer de GNL si nécessaire
	return (map);
}


int	main(void)
{
	int		fd = open("maps/valid/valid2.ber", O_RDONLY);
	char	**map;
	int		i = 0;

	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	map = getmap(fd);
	if (!map)
		return (1);
	while (map[i])
		printf("%s", map[i++]); // pas \n car get_next_line le garde
	return (0);
}