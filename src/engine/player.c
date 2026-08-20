#include "cube.h"

static void	set_camera(t_game *g, double dir_x, double dir_y)
{
	g->dir_x = dir_x;
	g->dir_y = dir_y;
	g->plane_x = -dir_y * FOV_PLANE;
	g->plane_y = dir_x * FOV_PLANE;
}

void	init_player(t_game *g)
{
	g->pos_x = g->scene->start_x;
	g->pos_y = g->scene->start_y;
	if (g->scene->start_dir == 'N')
		set_camera(g, 0.0, -1.0);
	else if (g->scene->start_dir == 'S')
		set_camera(g, 0.0, 1.0);
	else if (g->scene->start_dir == 'E')
		set_camera(g, 1.0, 0.0);
	else
		set_camera(g, -1.0, 0.0);
}
