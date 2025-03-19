
#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./include/MLX42/include/MLX42/MLX42.h"

# define WIDTH	1820
# define HEIGHT	1200

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_point;

typedef struct s_map
{
	t_point		*points;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			rows;
	int			collums;
	int			p_total;
	char		*name;
	int			max;
	int			min;
	float		scale;
	float		scalez;
	float		anglex;
	float		angley;
	int			offx;
	int			offy;
}	t_map;

typedef struct s_bresh
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				e;
	int				e2;
	unsigned int	color;
	int				cstep;
}	t_bresh;

int		main(int argc, char *argv[]);
void	ft_read_file(char *file, t_map *map);
void	ft_map_construction(t_map *map);
void	ft_get_scales(t_map *map);
void	ft_modify_points(t_map *map);
void	ft_set_color(char *num, t_point *buf, int j);
void	ft_color_flow(t_point *p1, t_point *p2, t_bresh *bresh, float i);
void	ft_error_free(t_map	*map, int exit_value);
void	ft_map_read_err(t_map *map, char *line, int fd);

#endif
