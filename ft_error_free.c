
#include "fdf.h"

void	ft_error_free(t_map	*map, int exit_value)
{
	if (map->points)
		free (map->points);
	if (map)
		free (map);
	exit (exit_value);
}

void	ft_map_read_err(t_map *map, char *line, int fd)
{
	if (line)
		free (line);
	close (fd);
	ft_error_free(map, 1);
}
