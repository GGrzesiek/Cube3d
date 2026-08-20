#include "cube.h"

static int	is_wall_cell(t_game *g, int x, int y)
{
	char	c;

	if (x < 0 || x >= g->scene->map.width)
		return (1);
	if (y < 0 || y >= g->scene->map.height)
		return (1);
	c = g->scene->map.grid[y][x];
	return (c == '1' || c == ' ');
}

static void	run_dda(t_game *g, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		hit = is_wall_cell(g, r->map_x, r->map_y);
	}
}

void	cast_ray(t_game *g, t_ray *r, int x)
{
	init_ray(g, r, x);
	run_dda(g, r);
	if (r->side == 0)
		r->perp_dist = r->side_x - r->delta_x;
	else
		r->perp_dist = r->side_y - r->delta_y;
	if (r->perp_dist < 0.0001)
		r->perp_dist = 0.0001;
}
