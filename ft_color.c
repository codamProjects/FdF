
#include "fdf.h"

void	ft_color_flow(t_point *p1, t_point *p2, t_bresh *bresh, float i)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	r = (p1->color >> 24) & 0xFF;
	g = (p1->color >> 16) & 0xFF;
	b = (p1->color >> 8) & 0xFF;
	a = p1->color & 0xFF;
	i = i / bresh->cstep;
	if (bresh->cstep >= i && i != 0)
	{
		r = (int)(r * (1 - i) + ((p2->color >> 24) & 0xFF) * i);
		g = (int)(g * (1 - i) + ((p2->color >> 16) & 0xFF) * i);
		b = (int)(b * (1 - i) + ((p2->color >> 8) & 0xFF) * i);
		a = (int)(a * (1 - i) + (p2->color & 0xFF) * i);
	}
	bresh->color = ((r << 24) | (g << 16) | (b << 8) | a);
}

static int	ft_hex_rgba(char a)
{
	int		i;
	char	*str;

	str = "0123456789ABCDEF";
	i = 0;
	if (!a)
		return (0);
	while (str[i])
	{
		if (ft_toupper(a) == str[i])
			return (i);
		i++;
	}
	return (0);
}

void	ft_set_color(char *num, t_point *buf, int pos)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (ft_isdigit(num[i]))
		i++;
	if (num[i] == ',')
		i++;
	if (num[i++] == '0' && num[i++] == 'x')
	{
		while (num[i])
		{
			x = x * 16 + ft_hex_rgba(num[i]);
			i++;
		}
		buf[pos].color = (x * 256) + 0xFF;
	}
	else
		buf[pos].color = 0xFFFFFFFF;
}
