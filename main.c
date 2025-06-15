#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "My_libft/headers/libft.h"

char	**getmap(int fd);
void	check_map(char **map);
void free_tab(char **map);
int	name_checker(char *str);

int	main(void)
{
	int		fd;
	char	**map;
	int		i;

	//MAPS INVALID
	char *map_duplicate_exit = "maps/invalid/duplicate_exit.ber";
	char *map_duplicate_player = "maps/invalid/duplicate_player.ber";
	char *map_empty_file = "maps/invalid/empty_file.ber";
	char *map_empty_line_at_start = "maps/invalid/empty_line_at_start.ber";
	char *map_empty_line_in_between = "maps/invalid/empty_line_in_between.ber";
	char *map_invalid_entities = "maps/invalid/invalid_entities.ber";
	char *map_no_coins = "maps/invalid/no_coins.ber";
	char *map_no_coins_path = "maps/invalid/no_coins_path.ber";
	char *map_no_corner_walls = "maps/invalid/no_corner_walls.ber";
	char *map_no_exit = "maps/invalid/no_exit.ber";
	char *map_no_exit_path = "maps/invalid/no_exit_path.ber";
	char *map_no_outter_walls = "maps/invalid/no_outter_walls.ber";
	char *map_no_player = "maps/invalid/no_player.ber";
	char *map_non_rectangular = "maps/invalid/non_rectangular.ber";
	char *map_one_character = "maps/invalid/one_character.ber";
	char *map_invalid5 = "maps/valid";

	//MAPS VALIDES
	char *map_minimal_horizontal = "maps/valid/minimal_horizontal.ber";
	char *map_minimal_vertical = "maps/valid/minimal_vertical.ber";
	char *map_valid1 = "maps/valid/valid1.ber";
	char *map_valid2 = "maps/valid/valid2.ber";
	char *map_valid3 = "maps/valid/valid3.ber";
	char *map_valid4 = "maps/valid/valid4.ber";
	char *map_valid5 = "maps/valid/valid5.ber";

	i = 0;
	//fd = open(map_duplicate_exit, O_RDONLY);
	name_checker(map_valid3);
	fd = open(map_valid3, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	map = getmap(fd);
	if (!map)
		return (1);
	while (map[i])
		printf("%s", map[i++]);
	printf("\n");
	printf("map checking >>>> ");
	check_map(map);
	free_tab(map);
	return (0);
}
