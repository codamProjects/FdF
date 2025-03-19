
#include "fdf.h"

void	ft_get_scales(t_map *map)
{
	float	a;
	float	b;

	a = (WIDTH / (map->rows + map->collums));
	b = ((HEIGHT - map->max + map->min) / (map->collums + map->rows));
	if (a < b)
		map->scale = a;
	else
		map->scale = b;
	if (map->scale == 0)
		map->scale = 1;
	if (abs(map->max - map->min) > map->rows + map->collums)
		map->scalez = map->scale / abs(map->max - map->min);
	else
		map->scalez = map->scale / 2;
	map->offx = (int)((WIDTH - map->collums) / 2);
	map->offy = (int)((HEIGHT - map->rows + map->max) / 2);
}

void	ft_modify_points(t_map *map)
{
	int		i;
	float	x;
	float	y;
	float	z;

	i = 0;
	map->anglex *= (M_PI / 180);
	map->angley *= (M_PI / 180);
	while (i < map->p_total)
	{
		z = map->points[i].z * map->scalez;
		x = map->points[i].x * map->scale;
		y = map->points[i].y * map->scale;
		map->points[i].x = (int)((x - y) * cos(map->anglex));
		map->points[i].y = (int)((x + y) * sin(map->angley) - z);
		map->points[i].x += map->offx;
		map->points[i].y += map->offy; 
		i++;
	}
}
