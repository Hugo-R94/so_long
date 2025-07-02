/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrouchy <hrouchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:17:13 by hrouchy           #+#    #+#             */
/*   Updated: 2025/07/02 17:59:06 by hrouchy          ###   ########.fr       */
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
		return (1);
	}
	return (0);
}

static char	**add_line_to_map(char **map, char *line, int i)
{
	char	**tmp;

	tmp = ft_realloc(map, i);
	if (!tmp)
	{
		free(line);
		free_tab(map); 
		return (NULL);
	}
	map = tmp;

	map[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!map[i])
	{
		free(line);
		free_tab(map);
		return (NULL);
	}
	ft_strcpy(map[i], line);
	free(line);
	return (map);
}

char	**getmap(int fd)
{
	char	**map;
	char	*line;
	int		i;
	char	**tmp;

	map = NULL;
	line = NULL;
	i = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		map = add_line_to_map(map, line, i++);
		if (!map)
			return (NULL);
		line = get_next_line(fd, 0);
	}
	tmp = ft_realloc(map, i);
	if (!tmp)
	{
		free_tab(map);
		return (NULL);
	}
	map = tmp;
	map[i] = NULL;
	return (map);
}
