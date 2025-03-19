
#include "fdf.h"

static void	ft_row_points(t_map *map, t_point *buf, char **row)
{
	int	x_value;
	int	y_value;
	int	old_size;
	int	pos;

	old_size = map->p_total - map->collums;
	y_value = map->rows - 1;
	x_value = 0;
	while (row && row[x_value])
	{
		pos = x_value + old_size;
		buf[pos].x = x_value;
		buf[pos].y = y_value;
		buf[pos].z = ft_atoi(row[x_value]);
		if (map->max < buf[pos].z)
			map->max = buf[pos].z;
		if (map->min > buf[pos].z)
			map->min = buf[pos].z;
		ft_set_color(row[x_value], buf, pos);
		x_value++;
	}
	ft_free_ptr_array((void**)row);
}

static t_point	*ft_new_row(t_map *map, char *line)
{
	t_point	*buf;
	int		i;
	int		old_size;

	i = 0;
	old_size = map->p_total - map->collums;
	buf = (t_point *)malloc(map->p_total * sizeof(t_point));
	if (!buf)
		return (NULL);
	if (map->points)
	{
		while (i < old_size)
		{
			buf[i].x = map->points[i].x;
			buf[i].y = map->points[i].y;
			buf[i].z = map->points[i].z;
			buf[i].color = map->points[i].color;
			i++;
		}
		free (map->points);
	}
	ft_row_points(map, buf, ft_split(line, ' '));
	if (line)
		free (line);
	return (buf);
}

void	ft_read_file(char *file, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error_free(map, 1);
	line = get_next_line(fd);
	map->collums = ft_word_count(line);
	while (line)
	{
		if (ft_word_count(line) != map->collums) 
			ft_map_read_err(map, line, fd);
		map->rows++;
		map->p_total = map->rows * map->collums;
		map->points = ft_new_row(map, line);
		if (!map->points)
			ft_map_read_err(map, line, fd);
		line = get_next_line(fd);
	}
	close (fd);
	if (line)
		free (line);
	ft_map_construction(map);
}
