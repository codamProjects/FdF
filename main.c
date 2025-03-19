
#include "fdf.h"

static void	ft_set_map(t_map *map)
{
	map->anglex = 30.0;
	map->angley = 30.0;
	map->scalez = 1.0;
	map->scale = 1.0;
	map->offx = (int)(WIDTH / 2);
	map->offy = (int)(HEIGHT / 2);
	map->rows = 0;
	map->collums = 0;
	map->p_total = 0;
	map->min = 2147483647;
	map->max = -2147483648;
	map->points = NULL;
}

static char	*ft_check_file(char *file)
{
	char	*name;

	if (!file)
		return (NULL);
	name = ft_strrchr(file, 47);
	if (name)
		name++;
	else if (!name)
		name = file;
	if (ft_strncmp(ft_strrchr(name, 46), ".fdf", 5) == 0)
		return (name);
	else
		return (NULL);
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	if (argc != 2)
	{
		write(1, "error\n", 6);
		exit (1);
	}
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		exit (1);
	map->name = ft_check_file(argv[1]);
	ft_set_map(map);
	if (map->name)
		ft_read_file(argv[1], map);
	else
		ft_error_free(map, 1);
	return (0);
}
