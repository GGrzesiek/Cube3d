#include "cube.h"

static void	set_step(t_game *g, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - g->pos_x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (g->pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - g->pos_y) * r->delta_y;
	}
}

/* 1e30 stands in for infinity when a direction component is 0 */
void	init_ray(t_game *g, t_ray *r, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_W - 1.0;
	r->dir_x = g->dir_x + g->plane_x * camera_x;
	r->dir_y = g->dir_y + g->plane_y * camera_x;
	r->map_x = (int)g->pos_x;
	r->map_y = (int)g->pos_y;
	if (r->dir_x == 0.0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->dir_x);
	if (r->dir_y == 0.0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->dir_y);
	set_step(g, r);
}
