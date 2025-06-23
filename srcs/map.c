/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugz <hugz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:13 by hrouchy           #+#    #+#             */
/*   Updated: 2025/06/23 12:08:29 by hugz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

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

int	name_checker(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (ft_strcmp(str + len - 4, ".ber") == 0)
	{
		printf("C'est bien un .ber\n");
		return (1);
	}
	printf("C'est pas un .ber\n");
	return (0);
}

char	**getmap(int fd)
{
	char	**map;
	char	*line;
	int		i;

	map = NULL;
	i = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		map = ft_realloc(map, i);
		map[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!map[i])
			return (NULL);
		ft_strcpy(map[i], line);
		free(line);
		i++;
		line = get_next_line(fd, 0);
	}
	map = ft_realloc(map, i);
	map[i] = NULL;
	line = get_next_line(fd, 1);
	return (map);
}

// int	main(void)
// {
// 	int		fd;
// 	char	**map;
// 	int		i;

// 	i = 0;
// 	fd = open("maps/valid/valid5.ber", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	map = getmap(fd);
// 	if (!map)
// 		return (1);
// 	while (map[i])
// 		printf("%s", map[i++]);
// 	printf("map checking >>>>\n");
// 	check_map(map);
// 	return (0);
// }
