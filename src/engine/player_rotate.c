#include "cube.h"

static void	rotate_vec(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	rotate_player(t_game *g)
{
	double	angle;

	angle = ROT_SPEED * g->frame_time;
	if (g->keys[KEY_LEFT])
	{
		rotate_vec(&g->dir_x, &g->dir_y, -angle);
		rotate_vec(&g->plane_x, &g->plane_y, -angle);
	}
	if (g->keys[KEY_RIGHT])
	{
		rotate_vec(&g->dir_x, &g->dir_y, angle);
		rotate_vec(&g->plane_x, &g->plane_y, angle);
	}
}
