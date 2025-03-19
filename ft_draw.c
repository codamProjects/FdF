
#include "fdf.h"

static void	ft_get_bresh(t_bresh *bresh, t_point p1, t_point p2)
{
	bresh->sx = 1;
	if (p1.x >= p2.x)
		bresh->sx = -1;
	bresh->sy = 1;
	if (p1.y >= p2.y)
		bresh->sy = -1;
	bresh->dx = abs(p2.x - p1.x);
	bresh->dy = abs(p2.y - p1.y);
	bresh->e = bresh->dx - bresh->dy;
	if (bresh->dy < bresh->dx)
		bresh->cstep = bresh->dx;
	else if (bresh->dy > bresh->dx)
		bresh->cstep = bresh->dy;
	else
		bresh->cstep = 0;
	bresh->color = p1.color;
}

static void	ft_draw_line(mlx_image_t *img, t_point p1, t_point p2)
{
	t_bresh	bresh;
	int		i;

	ft_get_bresh(&bresh, p1, p2);
	i = 0;
	while (1)
	{
		if (p1.x < WIDTH && p1.x >= 0 && p1.y < HEIGHT && p1.y >= 0)
			mlx_put_pixel(img, p1.x, p1.y, bresh.color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		bresh.e2 = 2 * bresh.e;
		if (bresh.e2 > -bresh.dy)
		{
			bresh.e -= bresh.dy;
			p1.x += bresh.sx;
		}
		if (bresh.e2 < bresh.dx)
		{
			bresh.e += bresh.dx;
			p1.y += bresh.sy;
		}
		if (bresh.color != p2.color)
			ft_color_flow(&p1, &p2, &bresh, ++i);
	}
}

static void	ft_get_points(mlx_image_t *img, t_map *map)
{
	int	i;

	i = 0;
	ft_modify_points(map);
	while (i < map->p_total)
	{
		if ((i + 1) % map->collums != 0 && (i + 1) < map->p_total)
			ft_draw_line(img, map->points[i], map->points[i + 1]);
		if (i + map->collums < map->p_total)
			ft_draw_line(img, map->points[i], map->points[i + map->collums]);
		i++;
	}
}

static void	ft_close_key(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
}

void	ft_map_construction(t_map *map)
{
	if (map->rows != 0 && map->collums != 0)
		ft_get_scales(map);
	map->mlx = mlx_init(WIDTH, HEIGHT, map->name, true);
	if (!map->mlx)
		ft_error_free(map, 1);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img || mlx_image_to_window(map->mlx, map->img, 0, 0) < 0)
		ft_error_free(map, 1);
	if (map->rows > 0 && map->collums > 0)
		ft_get_points(map->img, map);
	mlx_key_hook(map->mlx, &ft_close_key, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	ft_error_free(map, 0);
}
